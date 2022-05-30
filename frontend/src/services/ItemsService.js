import http from '../http-common'
import getAuth from "@/get_auth";

class ItemsService {
    getAllItems() {
        return http.post('items', getAuth());
    }

    addItem(item) {
        return http.post('items/add', { item: item, authentication: getAuth() });
    }

    editItem(oldItemId, item) {
        return http.put('items/edit', { item: item, authentication: getAuth() }, { params: { oldItemId } });
    }

    deleteItem(item) {
        return http.post('items/delete', getAuth(), { params: { id: item.id } });
    }

    findItems(searchQuery) {
        return http.post('items/search', getAuth(), { params: { searchQuery } });
    }

    deleteItems(searchQuery) {
        return http.post('items/deleteItems', getAuth(), { params: { searchQuery } });
    }

    clear() {
        return http.post('items/clear', getAuth());
    }
}

export default new ItemsService();