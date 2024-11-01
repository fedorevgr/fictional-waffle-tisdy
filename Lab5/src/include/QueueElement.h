
#ifndef LAB5_SRC_INCLUDE_QUEUEELEMENT_H
#define LAB5_SRC_INCLUDE_QUEUEELEMENT_H

typedef struct {
    int cycles;
} Element;

typedef enum QueueStatus_
{
    Q_OK,
    Q_EMPTY,
    Q_FULL
} QueueStatus;

#endif //LAB5_SRC_INCLUDE_QUEUEELEMENT_H
