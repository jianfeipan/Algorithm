class Singleton {
public:
    // 获取实例的唯一全局访问点
    static Singleton& getInstance() {
        static Singleton instance; // 核心：局部静态变量
        return instance;
    }

    // 删除拷贝构造和赋值操作
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    Singleton() {} // 私有构造函数
};

template <typename T>
class SingletonBase {
public:
    static T& getInstance() {
        static T instance;
        return instance;
    }
    SingletonBase(const SingletonBase&) = delete;
    SingletonBase& operator=(const SingletonBase&) = delete;

protected:
    SingletonBase() {} 
};

// 使用方法：
class DatabaseManager : public SingletonBase<DatabaseManager> {
    friend class SingletonBase<DatabaseManager>; // 必须让基类能访问私有构造函数
private:
    DatabaseManager() {}
};

