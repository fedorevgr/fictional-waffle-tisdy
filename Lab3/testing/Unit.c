#include <check.h>
#include <stdlib.h>

Suite *posSuite(void);

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = posSuite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;

}