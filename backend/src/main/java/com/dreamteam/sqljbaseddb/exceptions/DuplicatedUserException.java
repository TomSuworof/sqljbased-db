package com.dreamteam.sqljbaseddb.exceptions;

public class DuplicatedUserException extends IllegalStateException {
    private static final String USER_FOUND = "Such user already exists";

    public DuplicatedUserException() {
        super(USER_FOUND);
    }

    public DuplicatedUserException(String msg) {
        super("[%s] %s".formatted(USER_FOUND, msg));
    }

    public DuplicatedUserException(String msg, Throwable cause) {
        super("[%s] %s".formatted(USER_FOUND, msg), cause);
    }
}
