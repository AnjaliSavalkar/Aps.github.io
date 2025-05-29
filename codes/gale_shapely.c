#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id;
    int preference[MAX];
    int assigned_warehouse;
    int is_free;
} Driver;

typedef struct {
    int id;
    int preference[MAX];
    int assigned_driver;
} Warehouse;

void initialize(Driver drivers[], Warehouse warehouses[], int n, int m) {
    for (int i = 0; i < n; i++) {
        drivers[i].id = i;
        drivers[i].assigned_warehouse = -1;
        drivers[i].is_free = 1;
        for (int j = 0; j < m; j++) {
            drivers[i].preference[j] = -1;
        }
    }
    for (int i = 0; i < m; i++) {
        warehouses[i].id = i;
        warehouses[i].assigned_driver = -1;
        for (int j = 0; j < n; j++) {
            warehouses[i].preference[j] = -1;
        }
    }
}

int prefers_new_driver(Warehouse* warehouse, int new_driver, int current_driver) {
    for (int i = 0; i < MAX; i++) {
        if (warehouse->preference[i] == new_driver) return 1;
        if (warehouse->preference[i] == current_driver) return 0;
    }
    return 0;
}

void gale_shapley(Driver drivers[], Warehouse warehouses[], int n, int m) {
    int free_drivers = n;
    while (free_drivers > 0) {
        for (int i = 0; i < n; i++) {
            if (drivers[i].is_free) {
                for (int j = 0; j < m; j++) {
                    int warehouse_id = drivers[i].preference[j];
                    Warehouse* warehouse = &warehouses[warehouse_id];
                    if (warehouse->assigned_driver == -1) {
                        drivers[i].assigned_warehouse = warehouse_id;
                        warehouse->assigned_driver = i;
                        drivers[i].is_free = 0;
                        free_drivers--;
                        break;
                    } else if (prefers_new_driver(warehouse, i, warehouse->assigned_driver)) {
                        int old_driver = warehouse->assigned_driver;
                        drivers[old_driver].is_free = 1;
                        drivers[old_driver].assigned_warehouse = -1;
                        warehouse->assigned_driver = i;
                        drivers[i].assigned_warehouse = warehouse_id;
                        drivers[i].is_free = 0;
                        break;
                    }
                }
            }
        }
    }
}

void print_result(Driver drivers[], Warehouse warehouses[], int n, int m) {
    printf("\nDriver-Warehouse Assignments:\n");
    for (int i = 0; i < n; i++) {
        printf("Driver %d is assigned to Warehouse %d\n", drivers[i].id, drivers[i].assigned_warehouse);
    }
}

int main() {
    Driver drivers[MAX];
    Warehouse warehouses[MAX];
    int n = 5, m = 5;

    initialize(drivers, warehouses, n, m);

    drivers[0].preference[0] = 0; drivers[0].preference[1] = 1; drivers[0].preference[2] = 2; drivers[0].preference[3] = 3; drivers[0].preference[4] = 4;
    drivers[1].preference[0] = 1; drivers[1].preference[1] = 0; drivers[1].preference[2] = 2; drivers[1].preference[3] = 3; drivers[1].preference[4] = 4;
    drivers[2].preference[0] = 2; drivers[2].preference[1] = 0; drivers[2].preference[2] = 1; drivers[2].preference[3] = 3; drivers[2].preference[4] = 4;
    drivers[3].preference[0] = 3; drivers[3].preference[1] = 0; drivers[3].preference[2] = 1; drivers[3].preference[3] = 2; drivers[3].preference[4] = 4;
    drivers[4].preference[0] = 4; drivers[4].preference[1] = 0; drivers[4].preference[2] = 1; drivers[4].preference[3] = 2; drivers[4].preference[4] = 3;

    warehouses[0].preference[0] = 0; warehouses[0].preference[1] = 1; warehouses[0].preference[2] = 2; warehouses[0].preference[3] = 3; warehouses[0].preference[4] = 4;
    warehouses[1].preference[0] = 1; warehouses[1].preference[1] = 0; warehouses[1].preference[2] = 2; warehouses[1].preference[3] = 3; warehouses[1].preference[4] = 4;
    warehouses[2].preference[0] = 2; warehouses[2].preference[1] = 0; warehouses[2].preference[2] = 1; warehouses[2].preference[3] = 3; warehouses[2].preference[4] = 4;
    warehouses[3].preference[0] = 3; warehouses[3].preference[1] = 0; warehouses[3].preference[2] = 1; warehouses[3].preference[3] = 2; warehouses[3].preference[4] = 4;
    warehouses[4].preference[0] = 4; warehouses[4].preference[1] = 0; warehouses[4].preference[2] = 1; warehouses[4].preference[3] = 2; warehouses[4].preference[4] = 3;

    gale_shapley(drivers, warehouses, n, m);
    print_result(drivers, warehouses, n, m);

    return 0;
}
