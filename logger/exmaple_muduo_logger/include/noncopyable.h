class NonCopyAble {
 protected:
  NonCopyAble() {}
  ~NonCopyAble() {}

 private:
  NonCopyAble(const NonCopyAble&) = delete;
  NonCopyAble& operator=(const NonCopyAble&) = delete;
};
