#include <stdio.h>

typedef struct {
    char* server_name;
    int weight;
    int current_weight;
} Server;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int find_gcd(Server servers[], int n) {
    int result = servers[0].weight;
    for (int i = 1; i < n; i++) {
        result = gcd(result, servers[i].weight);
    }
    return result;
}

int max_weight(Server servers[], int n) {
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (servers[i].weight > max) {
            max = servers[i].weight;
        }
    }
    return max;
}

int weighted_round_robin(Server servers[], int n) {
    static int current_index = -1;
    static int current_weight = 0;
    int max_w = max_weight(servers, n);
    int gcd_w = find_gcd(servers, n);

    while (1) {
        current_index = (current_index + 1) % n;
        if (current_index == 0) {
            current_weight -= gcd_w;
            if (current_weight <= 0) {
                current_weight = max_w;
                if (current_weight == 0)
                    return -1;
            }
        }
        if (servers[current_index].weight >= current_weight)
            return current_index;
    }
}

int main() {
    Server servers[] = {
        {"Server A", 5, 0},
        {"Server B", 3, 0},
        {"Server C", 2, 0}
    };
    int n = sizeof(servers) / sizeof(servers[0]);

    // Simulate selecting 20 requests
    for (int i = 0; i < 20; i++) {
        int idx = weighted_round_robin(servers, n);
        printf("Request %d assigned to %s\n", i + 1, servers[idx].server_name);
    }

    return 0;
}
