#include <iostream>
#include <vector>

using namespace std;

vector<int> segment_tree;
int last_removed_soldier;

void update(int node_index) {
    segment_tree[node_index] = segment_tree[node_index * 2] + segment_tree[node_index * 2 + 1];
}

void build_segment_tree(int left, int right, int node_index) {
    segment_tree[node_index] = right - left + 1;
    if (left == right) return;
    int mid = (left + right) / 2;
    build_segment_tree(left, mid, node_index * 2);
    build_segment_tree(mid + 1, right, node_index * 2 + 1);
}

int query_sum(int query_left, int query_right, int segment_left, int segment_right, int node_index) {
    if (query_left <= segment_left && query_right >= segment_right) return segment_tree[node_index];
    int mid = (segment_left + segment_right) / 2;
    int sum = 0;
    if (query_left <= mid) sum += query_sum(query_left, query_right, segment_left, mid, node_index * 2);
    if (query_right > mid) sum += query_sum(query_left, query_right, mid + 1, segment_right, node_index * 2 + 1);
    return sum;
}

void remove_soldier(int position, int segment_left, int segment_right, int node_index) {
    if (segment_left == segment_right) { 
        segment_tree[node_index] = 0; 
        last_removed_soldier = segment_left; 
        return; 
    }
    int mid = (segment_left + segment_right) / 2;
    if (position <= segment_tree[node_index * 2]) remove_soldier(position, segment_left, mid, node_index * 2); 
    else remove_soldier(position - segment_tree[node_index * 2], mid + 1, segment_right, node_index * 2 + 1);
    update(node_index);
}

int main() {
    int total_soldiers, skip_distance; 
    cin >> total_soldiers >> skip_distance;
    segment_tree.resize(4 * total_soldiers);
    build_segment_tree(1, total_soldiers, 1);
    for (int i = 0; i < total_soldiers; ++i) {
        int position;
        if (last_removed_soldier == 0) position = skip_distance;
        else {
            int temp_sum = query_sum(1, last_removed_soldier, 1, total_soldiers, 1);
            position = (temp_sum + skip_distance) % segment_tree[1];
        }
        if (position == 0) position = segment_tree[1];
        remove_soldier(position, 1, total_soldiers, 1);
        cout << last_removed_soldier << " ";
    }
    return 0;
}
