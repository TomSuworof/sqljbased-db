package com.dreamteam.sqljbaseddb.entities;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.PositiveOrZero;
import java.sql.ResultSet;
import java.sql.SQLException;

@Getter
@Setter
@ToString
public class Item {
    @NotNull(message = "ID cannot be empty")
    private Long id;

    @NotBlank(message = "Name cannot be empty")
    private String name;

    @PositiveOrZero(message = "Amount cannot be negative")
    private Long amountAvailable;

    @PositiveOrZero(message = "Price cannot be negative")
    private Integer price;

    @NotBlank(message = "Item cannot be without color")
    private String color;

    @NotNull(message = "Boolean cannot be empty")
    private Boolean refurbished;

    public Item(Long id, String name, Long amountAvailable, Integer price, String color, Boolean refurbished) {
        this.id = id;
        this.name = name;
        this.amountAvailable = amountAvailable;
        this.price = price;
        this.color = color;
        this.refurbished = refurbished == null ? Boolean.FALSE : refurbished;
    }

    public static Item deserialize(ResultSet set) throws SQLException {
        return new Item(
                set.getLong("id"),
                set.getString("name"),
                set.getLong("amountAvailable"),
                set.getInt("price"),
                set.getString("color"),
                set.getBoolean("refurbished"));
    }
}
