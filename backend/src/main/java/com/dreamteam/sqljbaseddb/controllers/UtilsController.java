package com.dreamteam.sqljbaseddb.controllers;

import com.dreamteam.sqljbaseddb.entities.Authentication;
import com.dreamteam.sqljbaseddb.payload.request.AuthenticatedFormData;
import com.dreamteam.sqljbaseddb.services.UtilsService;
import lombok.RequiredArgsConstructor;
import org.springframework.core.io.FileSystemResource;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import javax.servlet.http.HttpServletResponse;
import java.io.File;

@Controller
@RequestMapping("/api/utils")
@CrossOrigin(origins = "http://localhost:8081")
@RequiredArgsConstructor
public class UtilsController {
    private final UtilsService utilsService;

    @PostMapping(value = "/backup")
    public @ResponseBody FileSystemResource getBackupFile(HttpServletResponse response, @RequestBody Authentication auth) {
        File backupFile = utilsService.getBackupFile(auth);

        response.setHeader("Content-Disposition", "inline; filename=" + backupFile.getName());
        response.setHeader("Content-Length", String.valueOf(backupFile.length()));

        return new FileSystemResource(backupFile);
    }

    @PostMapping("/backupXLSX")
    public @ResponseBody FileSystemResource getBackupFileXLSX(HttpServletResponse response, @RequestBody Authentication auth) {
        File backupFile = utilsService.getBackupFileXLSX(auth);

        response.setHeader("Content-Disposition", "inline; filename=" + backupFile.getName());
        response.setHeader("Content-Length", String.valueOf(backupFile.length()));

        return new FileSystemResource(backupFile);
    }

    @PostMapping(value = "/uploadBackupFile", consumes = {"multipart/form-data", "application/json"})
    public @ResponseBody void uploadBackupFile(@RequestBody AuthenticatedFormData formData) {
        utilsService.getFromBackup(formData.getFormData(), formData.getAuthentication());
    }
}
