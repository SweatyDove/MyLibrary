#ifndef MY_QUEUE_HPP
#define MY_QUEUE_HPP

#include <iostream>

namespace my {

    template <typename Type>
    class Queue {

    public:
        struct Item {
            Queue::Item* lastItem;         // Adress of the NEXT element of the queue
            Queue::Item* nextItem;         // Adress of the LAST element of the Queue

            Type content;
        };

    private:
        Queue::Item*  mb_frontElementOfQueue  {nullptr};
        Queue::Item*  mb_backElementOfQueue   {nullptr};

        int           mb_sizeOfQueue             {0};

    public:
        /*****************  Constructors and Destructors  *********************/
        Queue() = default;


        //======================================================================
        // NAME: Destructor
        // GOAL: Destructor releases all allocated memory for each element of
        //       list (struct my::List::Item).
        //======================================================================
        ~Queue()
        {
            while (mb_sizeOfQueue > 0) {
                this->removeFront();
            }
        }

        //======================================================================
        // NAME:
        // GOAL: Function provides an access to content of the FIRST element
        //       of the Queue.
        //======================================================================
        Type& getFrontContent()
        {
            return mb_frontElementOfQueue->content;
        }

        //======================================================================
        // NAME:
        // GOAL: Function provides an access to the LAST element of the Queue.
        //======================================================================
        Type& getBackContent()
        {
            return mb_backElementOfQueue->content;
        }

        //======================================================================
        // NAME: Getter
        // GOAL: Function returns adress of the FRONT item of list
        //======================================================================
        Queue::Item* getFrontAdress() const
        {
            return mb_frontElementOfQueue;
        }

        //======================================================================
        // NAME: Getter
        // GOAL: Function returns adress of the BACK item of list
        //======================================================================
        Queue::Item* getBackAdress() const
        {
            return mb_backElementOfQueue;
        }



        //======================================================================
        // NAME:
        // GOAL: Allocate new element of Queue with the specified @content and
        //       push it to the back of the Queue
        //======================================================================
        void pushBack(const Type& content)
        {
            // #### Allocate space for the new element of the Queue and bind it
            // #### with the previous one.
            Queue::Item* newItem {new Queue<Type>::Item};
            newItem->lastItem = nullptr;
            newItem->nextItem = nullptr;
            newItem->content = content;

            // #1 Queue is empty
            if (mb_sizeOfQueue == 0) {
                mb_backElementOfQueue = mb_frontElementOfQueue = newItem;
            }
            // #2 Add new item in the BACK of Queue
            else {
                newItem->nextItem = mb_backElementOfQueue;
                mb_backElementOfQueue->lastItem = newItem;
                mb_backElementOfQueue = newItem;
            }

            mb_sizeOfQueue++;

        }

        //======================================================================
        // NAME:
        // GOAL: Remove the front element from the Queue
        //======================================================================
        void removeFront()
        {
            Queue::Item* frontItem {mb_frontElementOfQueue};

            // #### Queue is empty
            if (mb_sizeOfQueue <= 0) {
                std::cerr << "\n[ERROR]::[my::Queue::removeFront()]:"
                          << "\nCan't remove element from an empty Queue."
                          << std::endl;
            }
            // #### Queue has ONE element
            else if (mb_sizeOfQueue == 1) {
                mb_frontElementOfQueue = mb_backElementOfQueue = nullptr;
                delete frontItem;
                --mb_sizeOfQueue;
            }
            // #### Queue has more than ONE element
            else {
                mb_frontElementOfQueue = mb_frontElementOfQueue->lastItem;
                mb_frontElementOfQueue->nextItem = nullptr;
                delete frontItem;
                --mb_sizeOfQueue;
            }

        }

        //======================================================================
        // NAME:
        // GOAL: Remove the front element from the Queue
        //======================================================================
        [[nodiscard]] int getSize() const
        {
            return mb_sizeOfQueue;
        }

    };

} // end-of-namespace_my

#endif // MY_QUEUE_HPP
