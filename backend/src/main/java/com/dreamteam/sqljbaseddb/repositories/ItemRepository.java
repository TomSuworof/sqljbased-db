package com.dreamteam.sqljbaseddb.repositories;

import com.dreamteam.sqljbaseddb.entities.Authentication;
import com.dreamteam.sqljbaseddb.entities.Item;

import java.sql.SQLException;
import java.util.List;
import java.util.Optional;

public interface ItemRepository {
    List<Item> findAll(Authentication auth);

    void save(Item item, Authentication auth);

    void deleteById(Long id, Authentication auth);

    Optional<Item> findItemById(Long id, Authentication auth);

    List<Item> findAllItemsById(Long id, Authentication auth);

    List<Item> findAllItemsByName(String name, Authentication auth);

    List<Item> findAllItemsByAmountAvailable(Long amountAvailable, Authentication auth);

    List<Item> findAllItemsByPrice(Integer price, Authentication auth);

    List<Item> findAllItemsByColor(String color, Authentication auth);

    List<Item> findAllItemsByRefurbished(Boolean refurbished, Authentication auth);

    void deleteAllItemsByName(String name, Authentication auth);

    void deleteAllItemsByAmountAvailable(Long amountAvailable, Authentication auth);

    void deleteAllItemsByPrice(Integer price, Authentication auth);

    void deleteAllItemsByColor(String color, Authentication auth);

    void deleteAllItemsByRefurbished(Boolean refurbished, Authentication auth);

    void deleteAllItems(Authentication auth) throws SQLException;
}
