package com.dreamteam.sqljbaseddb.repositories;

import com.dreamteam.sqljbaseddb.entities.Authentication;
import com.dreamteam.sqljbaseddb.entities.Item;
import com.dreamteam.sqljbaseddb.exceptions.DuplicatedItemException;
import org.springframework.stereotype.Repository;

import java.sql.*;
import java.util.*;

@Repository
public class ItemRepositoryImpl implements ItemRepository {
    @Override
    public List<Item> findAll(Authentication auth) {
        return NativeAdapter.findAllItems(auth.getDatabase(), auth.getUsername(), auth.getPassword())
                .stream()
                .map(Item::deserialize)
                .toList();
    }

    @Override
    public void save(Item item, Authentication auth) {
        NativeAdapter.addItemToDatabase(
                auth.getDatabase(),
                auth.getUsername(),
                auth.getPassword(),

                item.getId(),
                item.getName(),
                item.getAmountAvailable(),
                item.getPrice(),
                item.getColor(),
                item.getRefurbished()
                );
    }

    @Override
    public Optional<Item> findItemById(Long id, Authentication auth) {
        List<Item> items = findItemsByParam("id", String.valueOf(id), auth);
        if (items.size() > 1) {
            throw new DuplicatedItemException();
        } else if (items.size() == 1) {
            return Optional.of(items.get(0));
        } else {
            return Optional.empty();
        }
    }

    @Override
    public List<Item> findAllItemsById(Long id, Authentication auth) {
        return findItemsByParam("id", String.valueOf(id), auth);
    }

    @Override
    public List<Item> findAllItemsByName(String name, Authentication auth) {
        return findItemsByParam("name", name, auth);
    }

    @Override
    public List<Item> findAllItemsByAmountAvailable(Long amountAvailable, Authentication auth) {
        return findItemsByParam("amountAvailable", String.valueOf(amountAvailable), auth);
    }

    @Override
    public List<Item> findAllItemsByPrice(Integer price, Authentication auth) {
        return findItemsByParam("price", String.valueOf(price), auth);
    }

    @Override
    public List<Item> findAllItemsByColor(String color, Authentication auth) {
        return findItemsByParam("color", color, auth);
    }

    @Override
    public List<Item> findAllItemsByRefurbished(Boolean refurbished, Authentication auth) {
        return findItemsByParam("refurbished", String.valueOf(refurbished), auth);
    }

    @Override
    public void deleteById(Long id, Authentication auth) {
        deleteItemsByParam("id", String.valueOf(id), auth);
    }

    @Override
    public void deleteAllItemsByName(String name, Authentication auth) {
        deleteItemsByParam("name", name, auth);
    }

    @Override
    public void deleteAllItemsByAmountAvailable(Long amountAvailable, Authentication auth) {
        deleteItemsByParam("amountAvailable", String.valueOf(amountAvailable), auth);
    }

    @Override
    public void deleteAllItemsByPrice(Integer price, Authentication auth) {
        deleteItemsByParam("price", String.valueOf(price), auth);
    }

    @Override
    public void deleteAllItemsByColor(String color, Authentication auth) {
        deleteItemsByParam("color", color, auth);
    }

    @Override
    public void deleteAllItemsByRefurbished(Boolean refurbished, Authentication auth) {
        deleteItemsByParam("refurbished", String.valueOf(refurbished), auth);
    }

    @Override
    public void deleteAllItems(Authentication auth) throws SQLException {
        NativeAdapter.deleteAllItemsFromDatabase(auth.getDatabase(), auth.getUsername(), auth.getPassword());
    }

    private List<Item> findItemsByParam(String paramName, String paramValue, Authentication auth) {
        return NativeAdapter.findItemsByParam(auth.getDatabase(), auth.getUsername(), auth.getPassword(), paramName, paramValue)
                .stream()
                .map(Item::deserialize)
                .toList();
    }

    private void deleteItemsByParam(String paramName, String paramValue, Authentication auth) {
        NativeAdapter.deleteItemFromDatabase(auth.getDatabase(), auth.getUsername(), auth.getPassword(), paramName, paramValue);
    }
}
