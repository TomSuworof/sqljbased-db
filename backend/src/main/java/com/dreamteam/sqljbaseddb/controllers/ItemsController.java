package com.dreamteam.sqljbaseddb.controllers;

import com.dreamteam.sqljbaseddb.entities.Authentication;
import com.dreamteam.sqljbaseddb.entities.Item;
import com.dreamteam.sqljbaseddb.payload.request.AuthenticatedItem;
import com.dreamteam.sqljbaseddb.services.ItemService;
import lombok.RequiredArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import java.sql.SQLException;
import java.util.List;

@Controller
@RequestMapping("/api/items")
@CrossOrigin(origins = "http://localhost:8081")
@RequiredArgsConstructor
public class ItemsController {
    private final ItemService itemService;

    @PostMapping()
    public @ResponseBody ResponseEntity<List<Item>> getAllItems(@RequestBody Authentication auth) throws SQLException, ClassNotFoundException {
        return ResponseEntity.ok().body(itemService.getAllItems(auth));
    }

    @PostMapping("/add")
    public @ResponseBody void addItem(@RequestBody AuthenticatedItem item) throws SQLException, ClassNotFoundException {
        itemService.addItem(item.getItem(), item.getAuthentication());
    }

    @PutMapping("/edit")
    public @ResponseBody void editItem(@RequestBody AuthenticatedItem item, @RequestParam Long oldItemId) throws SQLException, ClassNotFoundException {
        itemService.editItem(oldItemId, item.getItem(), item.getAuthentication());
    }

    @PostMapping("/delete")
    public @ResponseBody void deleteItem(@RequestParam Long id, @RequestBody Authentication auth) throws SQLException, ClassNotFoundException {
        itemService.deleteItem(id, auth);
    }

    @PostMapping("/search")
    public @ResponseBody ResponseEntity<List<Item>> searchItems(@RequestParam String searchQuery, @RequestBody Authentication auth) throws SQLException, ClassNotFoundException {
        return ResponseEntity.ok().body(itemService.searchItems(searchQuery, auth));
    }

    @PostMapping("/deleteItems")
    public @ResponseBody void deleteItems(@RequestParam String searchQuery, @RequestBody Authentication auth) throws SQLException, ClassNotFoundException {
        itemService.deleteItemsBySearchQuery(searchQuery, auth);
    }

    @PostMapping("/clear")
    public @ResponseBody void deleteAllItems(@RequestBody Authentication auth) throws SQLException, ClassNotFoundException {
        itemService.deleteAllItems(auth);
    }
}
