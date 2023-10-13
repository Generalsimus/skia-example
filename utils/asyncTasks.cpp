


std::vector<std::future<void>> tasks_;
std::mutex mutex_;

template<typename Func, typename... Args>
void runAsyncTask(Func &&func, Args &&... args) {
    std::lock_guard<std::mutex> lock(mutex_);
    tasks_.emplace_back(std::async(std::launch::async, std::forward<Func>(func), std::forward<Args>(args)...));

};

void awaitAllAsyncTasks() {
    while (tasks_.size() != 0) {
        const std::future<void> &task = tasks_[0];
        if (task.valid()) {
            task.wait();
        }
        tasks_.erase(tasks_.begin() + 0);
    };
    tasks_.clear();
}

auto CreateAsyncAwaitGroup() {
    std::lock_guard<std::mutex> lock(mutex_);

    int startIndex = tasks_.size();


    return [startIndex]() {
        while (startIndex != tasks_.size()) {

            const std::future<void> &task = tasks_[startIndex];
            if (task.valid()) {
                task.wait();
            };
            tasks_.erase(tasks_.begin() + startIndex);
        };

    };
};
