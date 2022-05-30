package com.dreamteam.sqljbaseddb.exceptions;

public class UserNotFoundException extends IllegalStateException {
    private static final String USER_NOT_FOUND = "Such user does not exist";

    public UserNotFoundException() {
        super(USER_NOT_FOUND);
    }

    public UserNotFoundException(String msg) {
        super("[%s] %s".formatted(USER_NOT_FOUND, msg));
    }

    public UserNotFoundException(String msg, Throwable cause) {
        super("[%s] %s".formatted(USER_NOT_FOUND, msg), cause);
    }
}