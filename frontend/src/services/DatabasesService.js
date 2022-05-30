import http from '@/http-common';
import getAuth from "@/get_auth";

class DatabasesService {
    getAllDatabases() {
        return http.post('/databases', getAuth());
    }

    addDatabase(databaseName) {
        return http.post('databases/add', getAuth(), { params: { databaseName } });
    }

    removeDatabase(databaseName) {
        return http.post('databases/remove', getAuth(), { params: { databaseName }});
    }

    switchToDatabase(databaseName) {
        return http.post('databases/switchTo', getAuth(), { params: { databaseName } });
    }
}

export default new DatabasesService();