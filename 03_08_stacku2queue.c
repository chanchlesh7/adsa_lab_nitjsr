#include <stdio.h>
#include <stdlib.h>
#define MAX 100

// Queue structure
struct Queue {
    int arr[MAX];
    int front, rear;
};

// Initialize queue
void init(struct Queue *q) {
    q->front = q->rear = -1;
}

// Check if empty
int isEmpty(struct Queue *q) {
    return q->front == -1;
}

// Check if full
int isFull(struct Queue *q) {
    return (q->rear + 1) % MAX == q->front;
}

// Enqueue
void enqueue(struct Queue *q, int x) {
    if (isFull(q)) {
        printf("Queue Overflow\n");
        return;
    }
    if (q->front == -1) q->front = 0;
    q->rear = (q->rear + 1) % MAX;
    q->arr[q->rear] = x;
}

// Dequeue
int dequeue(struct Queue *q) {
    if (isEmpty(q)) {
        return -1;
    }
    int x = q->arr[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
    return x;
}

// Display queue contents
void displayQueue(struct Queue *q) {
    if (isEmpty(q)) {
        printf("Stack is empty\n");
        return;
    }
    int i = q->front;
    printf("Stack (top -> bottom): ");
    while (1) {
        printf("%d ", q->arr[i]);
        if (i == q->rear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}


//    METHOD 1: Stack using two queues (Push costly)
struct Stack1 {
    struct Queue q1, q2;
};

void initS1(struct Stack1 *s) {
    init(&s->q1);
    init(&s->q2);
}

void push1(struct Stack1 *s, int x) {
    // Step 1: Move all elements from q1 → q2
    while (!isEmpty(&s->q1)) {
        enqueue(&s->q2, dequeue(&s->q1));
    }

    // Step 2: Enqueue new element into q1
    enqueue(&s->q1, x);

    // Step 3: Move everything back q2 → q1
    while (!isEmpty(&s->q2)) {
        enqueue(&s->q1, dequeue(&s->q2));
    }
    printf("Pushed %d\n", x);
}

int pop1(struct Stack1 *s) {
    if (isEmpty(&s->q1)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return dequeue(&s->q1);
}

void display1(struct Stack1 *s) {
    displayQueue(&s->q1);
}


//    METHOD 2: Stack using two queues (Pop costly)
struct Stack2 {
    struct Queue q1, q2;
};

void initS2(struct Stack2 *s) {
    init(&s->q1);
    init(&s->q2);
}

void push2(struct Stack2 *s, int x) {
    enqueue(&s->q1, x);
    printf("Pushed %d\n", x);
}

int pop2(struct Stack2 *s) {
    if (isEmpty(&s->q1)) {
        printf("Stack Underflow\n");
        return -1;
    }

    // Move all except last from q1 → q2
    while (s->q1.front != s->q1.rear) {
        enqueue(&s->q2, dequeue(&s->q1));
    }

    // Last element is the "top"
    int popped = dequeue(&s->q1);

    // Swap q1 and q2
    struct Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;

    return popped;
}

void display2(struct Stack2 *s) {
    displayQueue(&s->q1);
}

//    MAIN MENU
int main() {
    int choice, val, method;

    printf("Choose Method:\n");
    printf("1. Push costly\n");
    printf("2. Pop costly\n");
    printf("Enter method: ");
    scanf("%d", &method);

    if (method == 1) {
        struct Stack1 s;
        initS1(&s);

        while (1) {
            printf("\n--- Stack Menu (Push Costly) ---\n");
            printf("1. Push\n2. Pop\n3. Display\n4. Exit\n");
            printf("Enter choice: ");
            scanf("%d", &choice);

            switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                push1(&s, val);
                break;
            case 2:
                val = pop1(&s);
                if (val != -1) printf("Popped %d\n", val);
                break;
            case 3:
                display1(&s);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
            }
        }
    } else if (method == 2) {
        struct Stack2 s;
        initS2(&s);

        while (1) {
            printf("\n--- Stack Menu (Pop Costly) ---\n");
            printf("1. Push\n2. Pop\n3. Display\n4. Exit\n");
            printf("Enter choice: ");
            scanf("%d", &choice);

            switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                push2(&s, val);
                break;
            case 2:
                val = pop2(&s);
                if (val != -1) printf("Popped %d\n", val);
                break;
            case 3:
                display2(&s);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
            }
        }
    } else {
        printf("Invalid method selected.\n");
    }

    return 0;
}