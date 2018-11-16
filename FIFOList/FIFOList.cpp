


#ifndef  FIFOLIST_H_


#define MAX_SIZE = 256;


/*
when queue is empty, we have front == back == 0

        0     1     2     3     4     5     6     7    QueueAllocSize = 8
     +-----+-----+-----+-----+-----+-----+-----+-----+
     |     |     |     |     |     |     |     |     |
     +-----+-----+-----+-----+-----+-----+-----+-----+
      front                                                                        
      back                                                                                                    


when we add something, we have front = 0, back = 1

        0     1     2     3     4     5     6     7     QueueAllocSize = 8
     +-----+-----+-----+-----+-----+-----+-----+-----+
     | #0  |     |     |     |     |     |     |     |
     +-----+-----+-----+-----+-----+-----+-----+-----+
      front  back
  

when we are full, this is what it looks like

        0     1     2     3     4     5     6     7     QueueAllocSize = 8
     +-----+-----+-----+-----+-----+-----+-----+-----+
     | #2  | #3  | #4  | #5  | #6  |     | #0  | #1  |
     +-----+-----+-----+-----+-----+-----+-----+-----+
     .............................. back  front.......


******************** two situations ********************

Situation 1

if back > front

        0     1     2     3     4     5     6     7     QueueAllocSize = 8
     +-----+-----+-----+-----+-----+-----+-----+-----+
     |     |     |     |     |     | #0  | #1  |     |
     +-----+-----+-----+-----+-----+-----+-----+-----+
                                    front.......back
     then curSize = back - front
     
else if back < front

        0     1     2     3     4     5     6     7     QueueAllocSize = 8
     +-----+-----+-----+-----+-----+-----+-----+-----+
     | #2  | #3  | #4  | #5  |     |     | #0  | #1  |
     +-----+-----+-----+-----+-----+-----+-----+-----+
     ......................... back       front.......

     then curSize = QueueAllocSize - front + back


******************** front == back *********************

The question really is that how we do we want to define the "front == back" case. Consider the following three examples

        0     1     2     3     4     5     6     7     QueueAllocSize = 8
     +-----+-----+-----+-----+-----+-----+-----+-----+
     |     |     |     |     |     |     |     |     |
     +-----+-----+-----+-----+-----+-----+-----+-----+
            front
             back

        0     1     2     3     4     5     6     7     QueueAllocSize = 8
     +-----+-----+-----+-----+-----+-----+-----+-----+
     |     | #0  |     |     |     |     |     |     |
     +-----+-----+-----+-----+-----+-----+-----+-----+
            front
             back

        0     1     2     3     4     5     6     7     QueueAllocSize = 8
     +-----+-----+-----+-----+-----+-----+-----+-----+
     | #7  | #0  | #1  | #2  | #3  | #4  | #5  | #6  |
     +-----+-----+-----+-----+-----+-----+-----+-----+
            front
             back

these three examples are all possibilities for the "front == back" case. So we pretty much have to stick with one if we want to avoid ambiguity
so, if we stick with "front == back" case is just empty, that means, we have to always leave one empty slot, like the "full" example. Otherwise, you have to use
special flags to indiciate which one of these three cases are you in when you have front == back. So we are just gonna waste one slot to save ourselves the trouble



        0     1     2     3     4     5     6     7     QueueAllocSize = 8
     +-----+-----+-----+-----+-----+-----+-----+-----+
     | #2  | #3  | #4  | #5  | #6  |     | #0  | #1  |
     +-----+-----+-----+-----+-----+-----+-----+-----+
     .............................. back  front.......


I do suppose that if you choose to store an extra m_curSize variable, you can use that as a flag to solve the ambiguity in the 
front == back case. I didnt really explore it in this project.
*/

template <class T>
class FifoList
{
    public:
          FifoList()
          {
               m_front = 0;
               m_back = 0;
               m_allocatedSize = 8;     // wrap around problem?
               m_array = new T[m_allocatedSize];
          }

          bool empty()
          {
               return m_front == m_back;
          }

          int size()
          {
               if (m_back > m_front)
               {
                    return m_back - m_front;
               }
               else if (m_back < m_front)
               {
                    return m_allocatedSize - m_front + m_back;
               }
               else
               {
                    return 0;
               }
          }

          T front()
          {
               return m_array[m_front];
          }

          T back()
          {
               return m_array[m_back];
          }

          void push(T value)
          {
               if (size() == m_allocatedSize - 1)
               {
                    resize();
               }

               // we always assume that m_back is valid, then 
               m_array[m_back] = value;
               if (m_back == m_allocatedSize - 1)
               {
                    m_back = 0;
               }
               else
               {
                    m_back++;
               }
          }

          void resize()
          {
               cout << "     >>>>>>> resizing " << endl;
               int newAllocatedSize = m_allocatedSize * 2;
               print();
               T* newArray = new T[newAllocatedSize];

               if (m_back > m_front)
               {
                    int newIndex = 0;
                    for (int i = m_front; i < m_back; i++)
                    {
                         newArray[newIndex++] = m_array[i];
                    }
                    m_front = 0;
                    m_back = newIndex;
               }
               else if (m_back < m_front)
               {
                    int newIndex = 0;
                    for (int i = m_front; i < m_allocatedSize; i++)
                    {
                         newArray[newIndex++] = m_array[i];
                    }

                    for (int i = 0; i < m_back; i++)
                    {
                         newArray[newIndex++] = m_array[i];
                    }
                    m_front = 0;
                    m_back = newIndex;
               }

               delete m_array;
               m_array = newArray;
               m_allocatedSize = newAllocatedSize;

               print();
          }


          void pop()
          {
               if (empty())
               {
                    cout << "Can't pop already empty " << endl;
                    return;
               }

               if (m_front == m_allocatedSize - 1)
               {
                    m_front = 0;
               }
               else
               {
                    m_front++;
               }
          }

          void print()
          {
               cout << "Print FifoList size is " << size() << endl;
               cout << "m_front " << m_front << " m_back " << m_back << " m_allocatedSize " << m_allocatedSize << endl;

               if (m_back > m_front)
               {                    
                    for (int i = 0; i < m_front; i++)
                    {
                         cout << "_ ";
                    }

                    for (int i = m_front; i < m_back; i++)
                    {
                         cout << m_array[i] << " ";
                    }

                    for (int i = m_back; i < m_allocatedSize; i++)
                    {
                         cout << "_ ";
                    }                    
               }
               else if (m_back < m_front)
               {                    
                    for (int i = 0; i < m_back; i++)
                    {
                         cout << m_array[i] << " ";
                    }

                    for (int i = m_back; i < m_front; i++)
                    {
                         cout << "_ ";
                    }

                    for (int i = m_front; i < m_allocatedSize; i++)
                    {
                         cout << m_array[i] << " ";
                    }                    
               }

               cout << endl << endl;
          }

     private:
          int m_front;
          int m_back;
          T* m_array;
          int m_allocatedSize;     // we will resize as needed
          // int m_curSize;        
		  // we currently deduce the size based on m_front and m_back, so we dont really need this variable
          // you can choose to cache the size if you choose it. Currently the size() function does have branching.
};


#endif // ! FIFOLIST_H_

