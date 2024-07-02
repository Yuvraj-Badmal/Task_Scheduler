#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

class TaskScheduler {
    priority_queue<pair<int, int>> tasks;
    unordered_map<int, int> taskMap; // Map to store task ID and its priority

public:
    void addTask(int id, int priority) {
        tasks.push({priority, id});
        taskMap[id] = priority;
    }

    void executeTask() {
        if (!tasks.empty()) {
            pair<int, int> nextTask = tasks.top();
            tasks.pop();
            taskMap.erase(nextTask.second);
            cout << "Executing Task: " << nextTask.second << " with Priority: " << nextTask.first << endl;
        } else {
            cout << "No tasks to execute!" << endl;
        }
    }

    void executeAllTasks() {
        cout << "\nExecuting All Tasks:\n";
        while (!tasks.empty()) {
            executeTask();
        }
    }

    void removeTask(int id) {
        if (taskMap.find(id) != taskMap.end()) {
            // Reconstruct priority queue without the task to remove
            priority_queue<pair<int, int>> tempQueue;
            while (!tasks.empty()) {
                pair<int, int> currentTask = tasks.top();
                tasks.pop();
                if (currentTask.second != id) {
                    tempQueue.push(currentTask);
                }
            }
            tasks = tempQueue;
            taskMap.erase(id);
            cout << "Task " << id << " removed successfully.\n";
        } else {
            cout << "Task ID " << id << " not found.\n";
        }
    }

    void viewTasks() {
        if (tasks.empty()) {
            cout << "No pending tasks.\n";
            return;
        }
        cout << "Pending Tasks:\n";
        priority_queue<pair<int, int>> tempQueue = tasks;
        while (!tempQueue.empty()) {
            pair<int, int> task = tempQueue.top();
            tempQueue.pop();
            cout << "Task ID: " << task.second << ", Priority: " << task.first << endl;
        }
    }
};

int main() {
    TaskScheduler scheduler;
    int taskId, taskPriority;
    char choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Task\n";
        cout << "2. Execute Next Task\n";
        cout << "3. Execute All Tasks\n";
        cout << "4. View All Tasks\n";
        cout << "5. Remove Task\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        int option;
        cin >> option;

        switch (option) {
            case 1:
                cout << "Enter Task ID: ";
                cin >> taskId;
                cout << "Enter Task Priority: ";
                cin >> taskPriority;
                scheduler.addTask(taskId, taskPriority);
                break;

            case 2:
                scheduler.executeTask();
                break;

            case 3:
                scheduler.executeAllTasks();
                break;

            case 4:
                scheduler.viewTasks();
                break;

            case 5:
                cout << "Enter Task ID to remove: ";
                cin >> taskId;
                scheduler.removeTask(taskId);
                break;

            case 6:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (true);

    return 0;
}
