#include "contactOpq.c"
#include "assert.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void test_mk_contact_should_return_ok(){
    printf("\t\tBEGIN - test_mk_contact_should_return_ok\n");
    // Arrange
    char* nome = "Nome";
    char* cognome = "Cognome";
    char* mobile = "12314241";
    char* url = "http://epico.com";

    // Act
    ContactPtr contact = mkContact(nome, cognome, mobile, url);

    // Assert
    assert(contact != NULL);
    assert(strcmp(contact->name, nome) == 0);
    assert(strcmp(contact->surname, cognome) == 0);
    assert(strcmp(contact->mobile, mobile) == 0);
    assert(strcmp(contact->url, url) == 0);
    free(contact);
    printf("\t\tEND - test_mk_contact_should_return_ok\n");
}

void test_mk_contact_name_null_should_return_null(){
    printf("\t\tBEGIN - test_mk_contact_name_null_should_return_null\n");
    // Arrange
    char* nome = NULL;
    char* cognome = "Cognome";
    char* mobile = "12314241";
    char* url = "http://epico.com";

    // Act
    ContactPtr contact = mkContact(nome, cognome, mobile, url);

    // Assert
    assert(contact == NULL);
    printf("\t\tEND - test_mk_contact_name_null_should_return_null\n");
}

void test_mk_contact_surname_null_should_return_null(){
    printf("\t\tBEGIN - test_mk_contact_surname_null_should_return_null\n");
    // Arrange
    char* nome = "nome";
    char* cognome = NULL;
    char* mobile = "12314241";
    char* url = "http://epico.com";

    // Act
    ContactPtr contact = mkContact(nome, cognome, mobile, url);

    // Assert
    assert(contact == NULL);
    printf("\t\tEND - test_mk_contact_surname_null_should_return_null\n");
}

void test_mk_contact(){
    printf("BEGIN\n\tTESTS: test_mk_contact\n");
    test_mk_contact_should_return_ok(); // TEST chiamata OK
    test_mk_contact_name_null_should_return_null();
    test_mk_contact_surname_null_should_return_null();
    printf("\tTESTS: test_mk_contact\nEND\n\t");
}

void test_ds_contact_ok_should_return_ok(){
    char* fun_name = "test_ds_contact_ok_should_return_ok";
    printf("\t\tBEGIN\t - %s\n",fun_name);
    // Arrange
    char* nome = "nome";
    char* cognome = "cognome";
    char* mobile = "12314241";
    char* url = "http://epico.com";
    ContactPtr contact = mkContact(nome, cognome, mobile, url);

    // Act
    dsContact(&contact);

    // Assert
    assert(contact == NULL);
    printf("\t\tEND\t - %s\n\n",fun_name);
}

void test_ds_contact_null_pointier_should_return_ok(){
    char* fun_name = "test_ds_contact_null_pointier_should_return_ok";
    printf("\t\tBEGIN\t - %s\n",fun_name);
    // Arrange
    
    ContactPtr null_pointier = NULL;
    // Act
    dsContact(NULL);

    // Assert
    assert(null_pointier == NULL);
    printf("\t\tEND\t - %s\n\n",fun_name);
}

void test_ds_contact_null_inner_pointier_should_return_ok(){
    char* fun_name = "test_ds_contact_null_inner_pointier_should_return_ok";
    printf("\t\tBEGIN\t - %s\n",fun_name);
    // Arrange
    
    ContactPtr null_pointier = NULL;
    // Act
    dsContact(&null_pointier);

    // Assert
    assert(null_pointier == NULL);
    printf("\t\tEND\t - %s\n\n",fun_name);
}

void test_ds_contact(){
    printf("BEGIN\n\tTESTS: test_ds_contact\n");
    test_ds_contact_ok_should_return_ok();
    test_ds_contact_null_pointier_should_return_ok();
    test_ds_contact_null_inner_pointier_should_return_ok();
    printf("\tTESTS: test_ds_contact\nEND\n\t");
}

void test_update_mobile_ok_should_return_ok(){
    char* fun_name = "test_ds_contact_null_inner_pointier_should_return_ok";
    printf("\t\tBEGIN\t - %s\n",fun_name);
    // Arrange
    char* old_mobile = "123456";
    char* new_mobile = "987654";
    
    // Act
    ContactPtr contact = mkContact("name", "surname", old_mobile, "epic.com");
    updateMobile(contact, new_mobile);

    // Assert
    assert(contact != NULL);
    assert(contact->mobile != old_mobile);
    assert(contact->mobile == new_mobile);
    free(contact);
    printf("\t\tEND\t - %s\n\n",fun_name);
}

void test_update_mobile_null_pointier_should_return_ok(){
    char* fun_name = "test_update_mobile_null_pointier_should_return_ok";
    printf("\t\tBEGIN\t - %s\n",fun_name);
    // Arrange
    
    // Act
    updateMobile(NULL, "12345");

    // Assert
    assert(true == true); // arrivati qui non si dovrebbe piantare
    printf("\t\tEND\t - %s\n\n",fun_name);
}

void test_update_mobile(){
    char* fun_name = "test_update_mobile";
    printf("BEGIN\n\tTESTS: %s\n",fun_name);
    test_update_mobile_ok_should_return_ok();
    test_update_mobile_null_pointier_should_return_ok();
    printf("\tTESTS: %s\nEND\n\t",fun_name);
}

void test_update_url_ok_should_return_ok(){
    char* fun_name = "test_update_url_ok_should_return_ok";
    printf("\t\tBEGIN\t - %s\n",fun_name);
    // Arrange
    char* old_url = "http://old_url.com";
    char* new_url = "http://new_url.com";
    
    // Act
    ContactPtr contact = mkContact("name", "surname", "12345", old_url);
    updateUrl(contact, new_url);

    // Assert
    assert(contact != NULL);
    assert(contact->url != old_url);
    assert(contact->url == new_url);
    free(contact);
    printf("\t\tEND\t - %s\n\n",fun_name);
}

void test_update_url_null_pointier_should_return_ok(){
    char* fun_name = "test_update_url_null_pointier_should_return_ok";
    printf("\t\tBEGIN\t - %s\n",fun_name);
    // Arrange
    char* old_url = "http://old_url.com";
    char* new_url = "http://new_url.com";
    
    // Act
    updateUrl(NULL, "1231245");

    // Assert
    assert(true == true); // qui vuol dire che non si e' spaccato niente
    printf("\t\tEND\t - %s\n\n",fun_name);
}

void test_update_url(){
    char* fun_name = "test_update_url";
    printf("BEGIN\n\tTESTS: %s\n",fun_name);
    test_update_url_ok_should_return_ok();
    test_update_url_null_pointier_should_return_ok();
    printf("\tTESTS: %s\nEND\n\t",fun_name);
}

void test_get_name_ok_should_return_ok(){
    char* fun_name = "test_get_name_ok_should_return_ok";
    printf("\t\tBEGIN\t - %s\n",fun_name);
    // Arrange
    
    // Act
    ContactPtr contact = mkContact("name", "surname", "12345", "epico.com");
    char* name = getName(contact);

    // Assert
    assert(contact != NULL);
    assert(name != NULL);
    assert(contact->name == name);
    free(contact);
    printf("\t\tEND\t - %s\n\n",fun_name);
}

void test_get_name_null_pointier_should_return_ok(){
    char* fun_name = "test_get_name_null_pointier_should_return_ok";
    printf("\t\tBEGIN\t - %s\n",fun_name);
    // Arrange
    
    // Act
    char* name = getName(NULL);

    // Assert
    assert(true == true); // se siamo qui e' finito bene
    printf("\t\tEND\t - %s\n\n",fun_name);
}

void test_get_name(){
    char* fun_name = "test_get_name";
    printf("BEGIN\n\tTESTS: %s\n",fun_name);
    test_get_name_ok_should_return_ok();
    test_get_name_null_pointier_should_return_ok();

    printf("\tTESTS: %s\nEND\n\t",fun_name);
}

void test_get_surname_ok_should_return_ok(){
    char* fun_name = "test_get_surname_ok_should_return_ok";
    printf("\t\tBEGIN\t - %s\n",fun_name);
    // Arrange
    ContactPtr contact = mkContact("name", "surname", "12345", "epico.com");
    
    // Act
    char* surname = getSurname(contact);

    // Assert
    assert(contact != NULL);
    assert(surname != NULL);
    assert(contact->surname == surname);
    free(contact);
    printf("\t\tEND\t - %s\n\n",fun_name);
}

void test_get_surname_null_pointier_should_return_ok(){
    char* fun_name = "test_get_surname_null_pointier_should_return_ok";
    printf("\t\tBEGIN\t - %s\n",fun_name);
    // Arrange
    
    // Act
    char* surname = getSurname(NULL);

    // Assert
    assert(true == true); // se siamo qui non si e' spaccato niente
    printf("\t\tEND\t - %s\n\n",fun_name);
}

void test_get_surname(){
    char* fun_name = "test_get_surname";
    printf("BEGIN\n\tTESTS: %s\n",fun_name);
    test_get_surname_ok_should_return_ok();
    test_get_surname_null_pointier_should_return_ok();

    printf("\tTESTS: %s\nEND\n\t",fun_name);
}

void test_get_mobile_ok_should_return_ok(){
    char* fun_name = "test_get_mobile_ok_should_return_ok";
    printf("\t\tBEGIN\t - %s\n",fun_name);
    // Arrange
    ContactPtr contact = mkContact("name", "surname", "12345", "epico.com");
    
    // Act
    char* mobile = getMobile(contact);

    // Assert
    assert(contact != NULL);
    assert(mobile != NULL);
    assert(contact->mobile == mobile);
    free(contact);
    printf("\t\tEND\t - %s\n\n",fun_name);
}

void test_get_mobile_null_mobile_should_return_ok(){
    char* fun_name = "test_get_mobile_null_mobile_should_return_ok";
    printf("\t\tBEGIN\t - %s\n",fun_name);
    // Arrange
    ContactPtr contact = mkContact("name", "surname", NULL, "epico.com");
    
    // Act
    char* mobile = getMobile(contact);

    // Assert
    assert(contact != NULL);
    assert(contact->mobile == mobile);
    free(contact);
    printf("\t\tEND\t - %s\n\n",fun_name);
}

void test_get_mobile_null_pointier_should_return_ok(){
    char* fun_name = "test_get_mobile_null_pointier_should_return_ok";
    printf("\t\tBEGIN\t - %s\n",fun_name);
    // Arrange
    
    // Act
    char* mobile = getMobile(NULL);

    // Assert
    assert(true == true); // se siamo qui e' tutto ok
    printf("\t\tEND\t - %s\n\n",fun_name);
}

void test_get_mobile(){
    char* fun_name = "test_get_mobile";
    printf("BEGIN\n\tTESTS: %s\n",fun_name);
    test_get_mobile_ok_should_return_ok();
    test_get_mobile_null_mobile_should_return_ok();
    test_get_mobile_null_pointier_should_return_ok();

    printf("\tTESTS: %s\nEND\n\t",fun_name);
}

void test_get_url_ok_should_return_ok(){
    char* fun_name = "test_get_url_ok_should_return_ok";
    printf("\t\tBEGIN\t - %s\n",fun_name);
    // Arrange
    ContactPtr contact = mkContact("name", "surname", "12345", "epico.com");
    
    // Act
    char* url = getUrl(contact);

    // Assert
    assert(contact != NULL);
    assert(url != NULL);
    assert(contact->url == url);
    free(contact);
    printf("\t\tEND\t - %s\n\n",fun_name);
}

void test_get_url_null_url_should_return_ok(){
    char* fun_name = "test_get_url_null_url_should_return_ok";
    printf("\t\tBEGIN\t - %s\n",fun_name);
    // Arrange
    ContactPtr contact = mkContact("name", "surname", "12345", NULL);
    
    // Act
    char* url = getUrl(contact);

    // Assert
    assert(contact != NULL);
    assert(contact->url == url);
    free(contact);
    printf("\t\tEND\t - %s\n\n",fun_name);
}

void test_get_url_null_pointier_should_return_ok(){
    char* fun_name = "test_get_url_null_pointier_should_return_ok";
    printf("\t\tBEGIN\t - %s\n",fun_name);
    // Arrange
    
    // Act
    char* url = getUrl(NULL);

    // Assert
    assert(true == true); // se siamo qui va bene

    printf("\t\tEND\t - %s\n\n",fun_name);
}

void test_get_url(){
    char* fun_name = "test_get_url";
    printf("BEGIN\n\tTESTS: %s\n",fun_name);
    
    test_get_url_ok_should_return_ok();
    test_get_url_null_url_should_return_ok();
    test_get_url_null_pointier_should_return_ok();

    printf("\tTESTS: %s\nEND\n\t",fun_name);
}

void test_equals_contact_equal_data_should_return_1(){
    char* fun_name = "test_equals_contact_equal_data_should_return_1";
    printf("\t\tBEGIN\t - %s\n",fun_name);
    // Arrange
    ContactPtr contact_1 = mkContact("name", "surname", "12345", "epico.com");
    ContactPtr contact_2 = mkContact("name", "surname", "12345", "epico.com");
    
    // Act
    int result = equalsContact(contact_1, contact_2);

    // Assert
    assert(contact_1 != NULL);
    assert(contact_2 != NULL);
    assert(result == 1);
    free(contact_1);
    free(contact_2);
    printf("\t\tEND\t - %s\n\n",fun_name);
}

void test_equals_contact_equal_data_case_should_return_1(){
    char* fun_name = "test_equals_contact_equal_data_case_should_return_1";
    printf("\t\tBEGIN\t - %s\n",fun_name);
    // Arrange
    ContactPtr contact_1 = mkContact("name", "surname", "12345", "epico.com");
    ContactPtr contact_2 = mkContact("NAME", "surname", "12345", "epico.com");
    
    // Act
    int result = equalsContact(contact_1, contact_2);

    // Assert
    assert(contact_1 != NULL);
    assert(contact_2 != NULL);
    assert(result == 1);
    free(contact_1);
    free(contact_2);
    printf("\t\tEND\t - %s\n\n",fun_name);
}

void test_equals_contact_diff_name_data_should_return_0(){
    char* fun_name = "test_equals_contact_diff_name_data_should_return_0";
    printf("\t\tBEGIN\t - %s\n",fun_name);
    // Arrange
    ContactPtr contact_1 = mkContact("name", "surname", "12345", "epico.com");
    ContactPtr contact_2 = mkContact("name_diff", "surname", "12345", "epico.com");
    
    // Act
    int result = equalsContact(contact_1, contact_2);

    // Assert
    assert(contact_1 != NULL);
    assert(contact_2 != NULL);
    assert(result == 0);
    free(contact_1);
    free(contact_2);
    printf("\t\tEND\t - %s\n\n",fun_name);
}


void test_equals_contact_diff_surname_data_should_return_0(){
    char* fun_name = "test_equals_contact_diff_surname_data_should_return_0";
    printf("\t\tBEGIN\t - %s\n",fun_name);
    // Arrange
    ContactPtr contact_1 = mkContact("name", "surname_diff", "12345", "epico.com");
    ContactPtr contact_2 = mkContact("name", "surname", "12345", "epico.com");
    
    // Act
    int result = equalsContact(contact_1, contact_2);

    // Assert
    assert(contact_1 != NULL);
    assert(contact_2 != NULL);
    assert(result == 0);
    free(contact_1);
    free(contact_2);
    printf("\t\tEND\t - %s\n\n",fun_name);
}

void test_equals_contact(){
    char* fun_name = "test_equals_contact";
    printf("BEGIN\n\tTESTS: %s\n",fun_name);
    
    test_equals_contact_equal_data_should_return_1();
    test_equals_contact_equal_data_case_should_return_1();
    test_equals_contact_diff_name_data_should_return_0();
    test_equals_contact_diff_surname_data_should_return_0();

    printf("\tTESTS: %s\nEND\n\t",fun_name);
}

void test_cmp_contact_equals_should_return_0(){
    char* fun_name = "test_equals_contact_diff_surname_data_should_return_0";
    printf("\t\tBEGIN\t - %s\n",fun_name);
    // Arrange
    ContactPtr contact_1 = mkContact("name", "surname", "12345", "epico.com");
    ContactPtr contact_2 = mkContact("name", "surname", "12345", "epico.com");
    
    // Act
    int result = cmpContact(contact_1, contact_2);

    // Assert
    assert(contact_1 != NULL);
    assert(contact_2 != NULL);
    assert(result == 0);
    free(contact_1);
    free(contact_2);
    printf("\t\tEND\t - %s\n\n",fun_name);
}

void test_cmp_contact_cnt_1_greater_should_return_1(){
    char* fun_name = "test_cmp_contact_cnt_1_greater_should_return_0";
    printf("\t\tBEGIN\t - %s\n",fun_name);
    // Arrange
    ContactPtr contact_1 = mkContact("zzzzz", "surname", "12345", "epico.com");
    ContactPtr contact_2 = mkContact("name", "surname", "12345", "epico.com");
    
    // Act
    int result = cmpContact(contact_1, contact_2);

    // Assert
    assert(contact_1 != NULL);
    assert(contact_2 != NULL);
    assert(result == 1);
    free(contact_1);
    free(contact_2);
    printf("\t\tEND\t - %s\n\n",fun_name);
}

void test_cmp_contact_cnt_2_greater_should_return_minus_1(){
    char* fun_name = "test_cmp_contact_cnt_2_greater_should_return_minus_1";
    printf("\t\tBEGIN\t - %s\n",fun_name);
    // Arrange
    ContactPtr contact_1 = mkContact("name", "surname", "12345", "epico.com");
    ContactPtr contact_2 = mkContact("zzzz", "surname", "12345", "epico.com");
    
    // Act
    int result = cmpContact(contact_1, contact_2);

    // Assert
    assert(contact_1 != NULL);
    assert(contact_2 != NULL);
    assert(result == -1);
    free(contact_1);
    free(contact_2);
    printf("\t\tEND\t - %s\n\n",fun_name);
}

void test_cmp_contact(){
    char* fun_name = "test_cmp_contact";
    printf("BEGIN\n\tTESTS: %s\n",fun_name);
    
    test_cmp_contact_equals_should_return_0();
    test_cmp_contact_cnt_1_greater_should_return_1();
    test_cmp_contact_cnt_2_greater_should_return_minus_1();
    
    printf("\tTESTS: %s\nEND\n\t",fun_name);
}

int main(){
    test_mk_contact();
    test_ds_contact();
    test_update_mobile();
    test_update_url();
    test_get_name();
    test_get_surname();
    test_get_mobile();
    test_get_url();
    test_equals_contact();
    test_cmp_contact();

    return 0;
}