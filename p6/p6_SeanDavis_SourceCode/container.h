#ifndef CONTAINER_H
#define	CONTAINER_H

class Container 
{
protected:
  int size;
public:
  Container(int siz);
  virtual ~Container();
  int getSize() const;
  virtual int* erase(int num) = 0;
  virtual int* find(int num) = 0;
  virtual int* insert(int num) = 0;
}; // class Container 

#endif	// CONTAINER_H

