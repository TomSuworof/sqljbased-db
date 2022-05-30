package com.dreamteam.sqljbaseddb.exceptions;

public class DuplicatedItemException extends IllegalStateException {
    private static final String ITEM_FOUND = "Such item already exists";

    public DuplicatedItemException() {
        super(ITEM_FOUND);
    }

    public DuplicatedItemException(String msg) {
        super("[%s] %s".formatted(ITEM_FOUND, msg));
    }

    public DuplicatedItemException(String msg, Throwable cause) {
        super("[%s] %s".formatted(ITEM_FOUND, msg), cause);
    }
}
