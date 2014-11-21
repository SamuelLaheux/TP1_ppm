
class gargouille
{

 public:
  // Create an empty constructor
  gargouille(void);
  // Create a constructor that take an argument : a picture of type gargouille
  gargouille(const gargouille& garg);
  void ppm_write_to_file(const char* nom);
  void ppm_read_from_file(const char* nom);
  void ppm_desaturate();
  void ppm_shrink(int factor);
  // Getters
  int GetWidth(void) const;
  int GetHeight(void) const;
  u_char* GetData(void) const;

 private:
  int width;
  int height;
  u_char* data;

};























