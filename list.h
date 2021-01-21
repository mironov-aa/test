#pragma once
#include <stdbool.h>
#include <stddef.h>

typedef struct node_t node_t;
struct node_t
{
    void* data;
    node_t* prev;
    node_t* next;
};

/**
 * @brief Контрольный блок
 */
typedef struct list_t list_t;
struct list_t
{
    const size_t sizeElement;///< Размер данных
    size_t countElements; ///< Количество элементов
    node_t* front; ///< Указатель на первый элемент
    node_t* back; ///< Указатель на последний элемент
};

/**
 * @brief Инициализация связного списка
 * 
 * @param list Указатель на указатель на контрольный блок
 * @param data Указатель на данные для первого элемента списка
 * @param sizeElement Размер элемента в байтах
 * @return true Инициализация успешна
 * @return false Ошибка инициализации
 */
bool listInit(list_t** list, void* data, const size_t sizeElement);

/**
 * @brief Освобождение памяти, занятой связным списком и его элементами
 * 
 * @param list Указатель на контрольный блок
 */
void listFree(list_t* list);

/**
 * @brief Обрезать список до заданного элемента
 * @param list Указатель на контрольный блок
 * @param pos Указатель на элемент, до которого нужно обрезать
 */
void listTruncate(list_t* list, node_t* pos);

/**
 * @brief Удаление элемента из списка
 * @param list Указатель на контрольный блок
 * @param pos Указатель на элемент
 */
void listRemoveNode(list_t* list, node_t* pos);

/**
 * @brief Извлечь первый элемент из списка
 * 
 * @param list Указатель на контрольный блок 
 * @param data Указатель на извлеченные данные
 */
void listPopBack(list_t* list, void* data);

/**
 * @brief Извлечь последний элемент из списка
 * 
 * @param list Указатель на контрольный блок 
 * @param data Указатель на извлеченные данные
 */
void listPopFront(list_t* list, void* data);

/**
 * @brief Передвижение по связному списку
 * @warning Если заданное количество больше, чем элементов в списке, то возвращается последний элемент
 * @param iter Исходный указатель на элемент
 * @param count Количество элементов
 * @param toFront Флаг направления перемещения
 * @return node_t* Указатель на элемент
 */
node_t* listMoveIter(node_t* iter, size_t count, bool toFront);

/**
 * @brief Добавление элемента к концу
 * 
 * @param list Указатель на контрольный блок
 * @param data Данные для создания нового элемента
 * @return node_t* Указатель на вставленный элемент
 */
node_t* listPushBack(list_t* list, void* data);

/**
 * @brief Добавление элемента к началу
 * 
 * @param list Указатель на контрольный блок
 * @param data Данные для создания нового элемента
 * @return node_t* Указатель на вставленный элемент
 */
node_t* listPushFront(list_t* list, void* data);

/**
 * @brief Добавление элемента после заданного
 * 
 * @param list Указатель на контрольный блок
 * @param pos Указатель на заданный элемент
 * @param data Данные для создания нового элемента
 * @return node_t* Указатель на вставленный элемент
 */
node_t* listInsert(list_t* list, node_t* pos, void* data);

/**
 * @brief Вывод всех элементов
 * 
 * @param list Указатель на контрольный блок
 * @param printData Указатель на функцию, реализующую вывод данного типа
 */
void listPrintAll(list_t* list, void (*printData)(const void*));