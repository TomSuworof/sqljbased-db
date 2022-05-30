import http from '@/http-common';
import getAuth from "@/get_auth";

class UserService {
    addUser(user) {
        return http.post('/users/add', {
            authentication: getAuth(),
            user: user,
        });
    }

    removeUser(username) {
        return http.post('users/remove', getAuth(), { params: { username } });
    }
}

export default new UserService();