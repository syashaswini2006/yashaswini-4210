#ifndef TASK_H
#define TASK_H

#include<iostream>
#include <string>
#include <ctime>

enum class Priority {
    LOW,
    MEDIUM,
    HIGH
};

class Task {
private:
    int id;
    std::string title;
    std::string description;
    Priority priority;
    std::time_t dueDate;
    bool completed;

public:
    Task();
    Task(int id, const std::string& title, const std::string& description, Priority priority, std::time_t dueDate);

    int getId() const;
    std::string getTitle() const;
    std::string getDescription() const;
    Priority getPriority() const;
    std::time_t getDueDate() const;
    bool isCompleted() const;

    void setTitle(const std::string& title);
    void setDescription(const std::string& description);
    void setPriority(Priority priority);
    void setDueDate(std::time_t dueDate);
    void setCompleted(bool completed);

    std::string toString() const;
    std::string serialize() const;
    static Task deserialize(const std::string& data);
};

#endif
#include "Task.h"
#include <sstream>
#include <iomanip>

Task::Task() : id(0), priority(Priority::LOW), dueDate(0), completed(false) {}

Task::Task(int id, const std::string& title, const std::string& description, Priority priority, std::time_t dueDate)
    : id(id), title(title), description(description), priority(priority), dueDate(dueDate), completed(false) {}

int Task::getId() const { return id; }
std::string Task::getTitle() const { return title; }
std::string Task::getDescription() const { return description; }
Priority Task::getPriority() const { return priority; }
std::time_t Task::getDueDate() const { return dueDate; }
bool Task::isCompleted() const { return completed; }

void Task::setTitle(const std::string& t) { title = t; }
void Task::setDescription(const std::string& d) { description = d; }
void Task::setPriority(Priority p) { priority = p; }
void Task::setDueDate(std::time_t dt) { dueDate = dt; }
void Task::setCompleted(bool c) { completed = c; }

std::string Task::toString() const {
    std::ostringstream oss;
    oss << "ID: " << id << "\n"
        << "Title: " << title << "\n"
        << "Description: " << description << "\n"
        << "Priority: ";
    switch(priority) {
        case Priority::LOW: oss << "Low"; break;
        case Priority::MEDIUM: oss << "Medium"; break;
        case Priority::HIGH: oss << "High"; break;
    }
    oss << "\nDue Date: " << std::asctime(std::localtime(&dueDate))
        << "Completed: " << (completed ? "Yes" : "No") << "\n";
    return oss.str();
}

std::string Task::serialize() const {
    std::ostringstream oss;
    oss << id << "|" << title << "|" << description << "|" << static_cast<int>(priority)
        << "|" << dueDate << "|" << completed;
    return oss.str();
}

Task Task::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string token;
    Task t;

    std::getline(iss, token, '|'); t.id = std::stoi(token);
    std::getline(iss, token, '|'); t.title = token;
    std::getline(iss, token, '|'); t.description = token;
    std::getline(iss, token, '|'); t.priority = static_cast<Priority>(std::stoi(token));
    std::getline(iss, token, '|'); t.dueDate = static_cast<std::time_t>(std::stol(token));
    std::getline(iss, token, '|'); t.completed = token == "1";

    return t;
}

