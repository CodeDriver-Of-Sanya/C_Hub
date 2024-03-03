#include "User.h"

User* createEmptyUser()
{
    User* u = calloc(1, sizeof(User));
    if (!u)
    {
        printf("createEmptyUser calloc failed!\n");
        return NULL;
    }

    return u;
}

void user_print(User u)
{
    printf("%-10llu %-10s %d\n", u.ID, u.password, u.type);
}

void user_save(User* u, FILE* f)
{
    char buf[BUFSIZ] = { 0 };
    sprintf(buf, "%llu\t%s\t%d\n", u->ID, u->password, u->type);
    fputs(buf, f);
}

bool is_commomUser(User* u)
{
    return u->type==UT_CommonUser;
}

bool is_bookAdmin(User* u)
{
    return u->type == UT_BookAdmin;
}

bool is_systemAdmin(User* u)
{
    return u->type == UT_SysAdmin;
}
