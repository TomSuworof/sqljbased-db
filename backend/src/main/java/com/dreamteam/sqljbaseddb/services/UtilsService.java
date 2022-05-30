package com.dreamteam.sqljbaseddb.services;

import com.dreamteam.sqljbaseddb.entities.Authentication;
import com.dreamteam.sqljbaseddb.entities.Item;
import lombok.RequiredArgsConstructor;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.ss.usermodel.Sheet;
import org.apache.poi.ss.usermodel.Workbook;
import org.apache.poi.xssf.streaming.SXSSFWorkbook;
import org.springframework.stereotype.Service;
import org.springframework.web.multipart.MultipartFile;

import java.io.*;
import java.sql.SQLException;
import java.util.List;

@Service
@RequiredArgsConstructor
public class UtilsService {
    private final ItemService itemService;

    public File getBackupFile(Authentication auth) {

        try {
            File csvFile = File.createTempFile("jdbcbased-bd", ".csv");
            PrintWriter writer = new PrintWriter(csvFile);

            List<Item> items = itemService.getAllItems(auth);

            items.stream()
                    .map(item -> "%d, %s, %d, %d, %s, %s;".formatted(item.getId(), item.getName(), item.getAmountAvailable(), item.getPrice(), item.getColor(), item.getRefurbished()))
                    .forEach(writer::println);

            writer.close();
            return csvFile;
        } catch (IOException | SQLException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    public File getBackupFileXLSX(Authentication auth) {
        try {
            Workbook workbook = new SXSSFWorkbook();
            Sheet sheet = workbook.createSheet("items");

            Row heading = sheet.createRow(0);
            heading.createCell(0).setCellValue("ID");
            heading.createCell(1).setCellValue("Name");
            heading.createCell(2).setCellValue("Amount available");
            heading.createCell(3).setCellValue("Price");
            heading.createCell(4).setCellValue("Color");
            heading.createCell(5).setCellValue("Refurbished");

            List<Item> items = itemService.getAllItems(auth);

            for (int i = 0; i < items.size(); i++) {
                Row row = sheet.createRow(i + 1);
                row.createCell(0).setCellValue(items.get(i).getId());
                row.createCell(1).setCellValue(items.get(i).getName());
                row.createCell(2).setCellValue(items.get(i).getAmountAvailable());
                row.createCell(3).setCellValue(items.get(i).getPrice());
                row.createCell(4).setCellValue(items.get(i).getColor());
                row.createCell(5).setCellValue(items.get(i).getRefurbished());
            }

            File xlsxFile = File.createTempFile("jdbcbased-db", ".xlsx");
            FileOutputStream outputStream = new FileOutputStream(xlsxFile);

            workbook.write(outputStream);
            workbook.close();
            outputStream.close();
            return xlsxFile;
        } catch (IOException | SQLException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    public void getFromBackup(MultipartFile file, Authentication auth) {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(file.getInputStream()))) {
            reader.lines()
                    .map(line -> {
                        String[] arr = line.substring(0, line.length() - 1).split(",");
                        return new Item(
                                Long.parseLong(arr[0]),
                                arr[1],
                                Long.parseLong(arr[2]),
                                Integer.parseInt(arr[3]),
                                arr[4],
                                Boolean.parseBoolean(arr[5]));
                    })
                    .forEach(item -> {
                        try {
                            itemService.addItem(item, auth);
                        } catch (SQLException | ClassNotFoundException e) {
                            throw new RuntimeException(e);
                        }
                    });

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
