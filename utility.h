//
// Created by Ante Marusic on 09/07/23.
//

#ifndef API_UTILITY_H
#define API_UTILITY_H
#define DEBUG

#ifdef DEBUG
#define SHOW printf
#else
#define SHOW // macros
#endif

enum boolean {
    false,
    true
};
#endif //API_UTILITY_H
