package com.dreamteam.sqljbaseddb.controllers;

import com.dreamteam.sqljbaseddb.entities.Authentication;
import com.dreamteam.sqljbaseddb.services.DatabasesService;
import lombok.RequiredArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import java.sql.SQLException;
import java.util.List;

@Controller
@RequestMapping("/api/databases")
@CrossOrigin(origins = "http://localhost:8081")
@RequiredArgsConstructor
public class DatabasesController {
    private final DatabasesService databasesService;

    @PostMapping()
    public @ResponseBody ResponseEntity<List<String>> getAllDatabases(@RequestBody Authentication auth) throws SQLException, ClassNotFoundException {
        return ResponseEntity.ok().body(databasesService.getAllDatabases(auth));
    }

    @PostMapping("/switchTo")
    public @ResponseBody void switchToDatabase(@RequestParam String databaseName, @RequestBody Authentication auth) throws SQLException, ClassNotFoundException {
        databasesService.switchToDatabase(databaseName, auth);
    }

    @PostMapping("/add")
    public @ResponseBody void addDatabase(@RequestParam String databaseName, @RequestBody Authentication auth) throws SQLException, ClassNotFoundException {
        databasesService.addDatabase(databaseName, auth);
    }

    @PostMapping("/remove")
    public @ResponseBody void removeDatabase(@RequestParam String databaseName, @RequestBody Authentication auth) throws SQLException, ClassNotFoundException {
        databasesService.deleteDatabase(databaseName, auth);
    }
}
