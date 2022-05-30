import http from '../http-common';
import getAuth from "@/get_auth";

class UtilsService {
    getBackupFile() {
        return http.post("utils/backup", getAuth(),
            {
                responseType: 'arraybuffer',
            });
    }

    getBackupFileXLSX() {
        return http.post("utils/backupXLSX", getAuth(),
            {
                responseType: 'arraybuffer',
            });
    }

    uploadBackupFile(formData) {
        alert("Not implemented");
        return http.post('utils/uploadBackupFile', {
                formData: formData,
                authentication: getAuth()
            }, {});
    }
}

export default new UtilsService();