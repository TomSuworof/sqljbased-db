package com.dreamteam.sqljbaseddb.entities;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
public class Authentication {
    private String username;
    private String password;
    private String database; // carries not auth info, but current database for operation
}
