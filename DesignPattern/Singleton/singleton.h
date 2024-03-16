#ifndef SINGLETON_H_
#define SINGLETON_H_

class Singleton {
  public:
    static Singleton *getInstance() {
        if (_instance == nullptr) {
            _instance = new Singleton();
        }
    }

  private:
    Singleton() {}
    Singleton(const Singleton &) = delete;

  private:
    static Singleton *_instance;
};

Singleton *Singleton::_instance = nullptr;

#endif // SINGLETON_H_
