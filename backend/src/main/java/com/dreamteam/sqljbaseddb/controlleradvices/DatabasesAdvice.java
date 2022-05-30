package com.dreamteam.sqljbaseddb.controlleradvices;

import com.dreamteam.sqljbaseddb.payload.response.ErrorResponse;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;

import javax.servlet.http.HttpServletRequest;
import java.sql.SQLException;
import java.util.Date;

@ControllerAdvice
public class DatabasesAdvice {

    @ExceptionHandler(SQLException.class)
    public ResponseEntity<ErrorResponse> handleDatabasesError(SQLException e, HttpServletRequest request) {
        HttpStatus status = HttpStatus.I_AM_A_TEAPOT;
        ErrorResponse response = new ErrorResponse(new Date(), status.value(), e.getMessage(), request.getRequestURI());

        e.printStackTrace();

        return ResponseEntity.status(status).body(response);
    }
}
