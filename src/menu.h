#ifndef __MENU_H
#define __MENU_H

#include <Arduino.h>

#include "constants.h"
#include <LinkedList.h>

namespace Menu {

    /**
     * @brief Enumeration type to deal with the type of a message item to connect it to a display method
     *
     */
    enum MenuItemType {
        VALUE,
        MESSAGE,
        SELECTION,
        MENU
    };

    /**
     * @brief Class to safe Items in a Menu
     *
     */
    class MenuItem {
        private:
            char* item;
            MenuItemType type;

        public:
            /**
             * @brief Empty Constructor for MenuItem::MenuItem
             *
             */
            MenuItem() {};
            /**
             * @brief Construct a new Menu Item by handing it a text of the item
             *
             * @param item      Item name
             */
            MenuItem(char* item, MenuItemType type) {
                this->item = item;
                this->type = type;
            };

            /**
             * @brief Get the Item text
             *
             * @return char*    text of the Item
             */
            char* getItem() { return item; };
            /**
             * @brief Set the Item test
             *
             * @param item      text of the Item
             */
            void setItem(char* item) { this->item = item; };

            /**
             * @brief Get the Type of the Item
             *
             * @return MenuItemType     Item type
             */
            MenuItemType getType() { return type; };
            /**
             * @brief Set the Type of the Item
             *
             * @param type      Item type
             */
            void setType(MenuItemType type) { this->type = type; };
    };

    /**
     * @brief   Class to save a List of MenuItems
     *          Wrapper for LinkedList
     *
     */
    class MenuList {
        private:
            LinkedList<MenuItem> list;

        public:
            /**
             * @brief Construct a new Menu List object
             *
             */
            MenuList() {};

            /**
             * @brief Get the Size of the List in elements
             *
             * @return uint16_t     Size of the Element
             */
            uint16_t getSize() { return (uint16_t) list.size(); };

            /**
             * @brief Add a MenuItem to the List
             *
             * @param item      Item to be added
             */
            void add(MenuItem item) { list.add(item); };
            /**
             * @brief Add a MenuItem to the List
             *
             * @param pos       Position of the Item in the List
             * @param item      Item to be added
             */
            void add(uint16_t pos, MenuItem item) { list.add(pos, item); };

            /**
             * @brief   Get an Item from the list based on its position
             *
             * @param pos       Position of the Item in the List
             * @return MenuItem MenuItem from the List
             */
            MenuItem get(uint16_t pos) { return list.get(pos); };

            /**
             * @brief   Change the MenuItem on an arbitrary position in the List
             *
             * @param pos       Position of the Item in the List
             * @param item      MenuItem to be changed
             */
            void set(uint16_t pos, MenuItem item) { list.set(pos, item); };

            /**
             * @brief   Remove a MenuList Item from the List at an arbirtary position
             *
             * @param pos       Position of the Item in the List
             */
            void remove(uint16_t pos) { list.remove(pos); };
    };

}

#endif