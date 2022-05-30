package com.dreamteam.sqljbaseddb.services;

import com.dreamteam.sqljbaseddb.entities.Authentication;
import com.dreamteam.sqljbaseddb.entities.Item;
import com.dreamteam.sqljbaseddb.exceptions.DuplicatedItemException;
import com.dreamteam.sqljbaseddb.exceptions.IllegalItemFormatException;
import com.dreamteam.sqljbaseddb.exceptions.ItemNotFoundException;
import com.dreamteam.sqljbaseddb.repositories.ItemRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.sql.SQLException;
import java.util.List;
import java.util.Optional;

@Service
@RequiredArgsConstructor
public class ItemService {
    private final ItemRepository itemRepository;

    public List<Item> getAllItems(Authentication auth) throws SQLException, ClassNotFoundException {
        return itemRepository.findAll(auth);
    }

    public void addItem(Item item, Authentication auth) throws SQLException, ClassNotFoundException {
        Optional<Item> duplicatedItem = itemRepository.findItemById(item.getId(), auth);
        if (duplicatedItem.isPresent()) {
            throw new DuplicatedItemException();
        } else {
            itemRepository.save(item, auth);
        }
    }

    public void editItem(Long oldItemId, Item item, Authentication auth) throws SQLException, ClassNotFoundException {
        deleteItem(oldItemId, auth);
        addItem(item, auth);
    }

    public void deleteItem(Long id, Authentication auth) throws SQLException, ClassNotFoundException {
        Optional<Item> itemOpt = itemRepository.findItemById(id, auth);
        if (itemOpt.isEmpty()) {
            throw new ItemNotFoundException();
        } else {
            itemRepository.deleteById(id, auth);
        }
    }

    public List<Item> searchItems(String searchQuery, Authentication auth) throws SQLException, ClassNotFoundException {
        String[] parts = searchQuery.split("=");
        String field = parts[0].toLowerCase();
        String value = parts[1];

        return switch (field) {
            case "id" -> itemRepository.findAllItemsById(Long.parseLong(value), auth);
            case "name" -> itemRepository.findAllItemsByName(value, auth);
            case "amountavailable" -> itemRepository.findAllItemsByAmountAvailable(Long.parseLong(value), auth);
            case "price" -> itemRepository.findAllItemsByPrice(Integer.parseInt(value), auth);
            case "color" -> itemRepository.findAllItemsByColor(value, auth);
            case "refurbished" -> itemRepository.findAllItemsByRefurbished(Boolean.parseBoolean(value), auth);
            default -> throw new IllegalItemFormatException();
        };
    }

    public void deleteItemsBySearchQuery(String searchQuery, Authentication auth) throws SQLException, ClassNotFoundException {
        String[] parts = searchQuery.split("=");
        String field = parts[0].toLowerCase();
        String value = parts[1];

        switch (field) {
            case "id" -> itemRepository.deleteById(Long.parseLong(value), auth);
            case "name" -> itemRepository.deleteAllItemsByName(value, auth);
            case "amountavailable" -> itemRepository.deleteAllItemsByAmountAvailable(Long.parseLong(value), auth);
            case "price" -> itemRepository.deleteAllItemsByPrice(Integer.parseInt(value), auth);
            case "color" -> itemRepository.deleteAllItemsByColor(value, auth);
            case "refurbished" -> itemRepository.deleteAllItemsByRefurbished(Boolean.parseBoolean(value), auth);
            default -> throw new IllegalItemFormatException();
        }
    }

    public void deleteAllItems(Authentication auth) throws SQLException, ClassNotFoundException {
        itemRepository.deleteAllItems(auth);
    }
}
