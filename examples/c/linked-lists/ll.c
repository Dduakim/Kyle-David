#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <errno.h>
#include <strings.h>
#include <unistd.h>


/*********************************************************************************/

static unsigned int num_tests  = 0;
static unsigned int num_passed = 0;
static unsigned int num_failed = 0;

void test_init() {
  num_tests  = 0;
  num_passed = 0;
  num_failed = 0;
}

void test_assert(const char* fname, int lnum, const char* funcname, unsigned int bval, const char* expr, const char* fail_msg) {
  ++num_tests;
  if (bval) {
    ++num_passed;
    return; // ok
  }

  ++num_failed;
  fprintf(stderr, "%s(%d).%s: FAIL: %s: %s\n", fname, lnum, funcname, fail_msg, expr);
}

unsigned int test_report () {
  if (num_failed > 0) {
    fprintf(stdout, "FAILED: %3.2f (%u) failed; %3.2f (%u) passed out of %u\n",
            100 * ((float)num_failed / (float)num_tests),
            num_failed,
            100 * ((float)num_passed / (float)num_tests),
            num_passed,
            num_tests);
    return num_failed;
  }

  fprintf(stdout, "PASSED: 100%% (%u) passed out of %u\n",
          num_passed,
          num_tests);
  return 0;
}

void test_report_and_exit () {
  if (test_report()) {
    exit(1);
  }

  exit(0);
}

#define ASSERT(pred,msg) test_assert(__FILE__, __LINE__, __FUNCTION__, pred, #pred, msg);

/*********************************************************************************/

/**
 * Linked List examples
 *
 *
 */

typedef struct Node {
  void*        value;
  struct Node* next;
} Node;

Node* ll_new() {
  return NULL;
}

void ll_perror_exit(const char* fname, int lnum, const char* funcname, const char* msg) {
  fprintf(stderr, "%s(%d).%s: ERROR: msg=%s: errno=%d; error=%s\n", fname, lnum, funcname, msg, errno, strerror(errno));
  exit(1);
}

Node* ll_alloc() {
  Node* n = (Node*)malloc(1 * sizeof(Node));
  if (!n) {
    ll_perror_exit(__FILE__, __LINE__, __FUNCTION__, "Error allocating memory for new node");
  }

  return n;
}

Node* ll_add(Node* head, void* value) {
  Node* nhead = ll_alloc();
  if (!nhead) {
    return NULL;
  }

  nhead->value = value;
  nhead->next = head;

  return nhead;
}

size_t ll_len(Node* head) {
  size_t len = 0;
  while (head) {
    ++len;
    head = head->next;
  }
  return len;
}

Node* ll_add_end(Node* head, void* value) {
  Node* nend = ll_alloc();
  if (!nend) {
    return NULL;
  }

  nend->value = value;
  nend->next = NULL;

  if (!head) {
    return nend;
  }

  Node* cur = head;
  while (cur->next) {
    cur = cur->next;
  }

  cur->next = nend;

  return head;
}


Node* ll_nth(Node* head, unsigned int nn) {
  while (head) {
    if (nn == 0) {
      return head;
    }

    head = head->next;
    --nn;
  }

  return NULL; // not found
}

void* ll_nth_value(Node* head, unsigned int nn) {
  Node* node = ll_nth(head, nn);

  if (node) {
    return node->value;
  }

  return NULL; // not found
}

Node* ll_pop(Node* head, void (vfree)(void*)) {
  if (!head) {
    return head;
  }

  Node* next = head->next;
  vfree(head->value);
  free(head);
  return next;
}


void ll_pretty_print(char* name, Node* head, void (*pprint) (FILE*, void*)) {
  Node* cur = head;
  printf("List{%s}|", name);
  while (cur) {
    printf("(");
    pprint(stdout, cur->value);

    if (!cur->next) {
      printf(",END)|");
      break;
    }

    printf(",*)->");
    cur = cur->next;
  }
  printf("\n");
}


void ll_pprint_pointer(FILE* fp, void* value) {
  fprintf(fp, "%p", value);
}

void ll_print(char *name, Node* head) {
  ll_pretty_print(name, head, ll_pprint_pointer);
}

void ll_vfree_noop(__attribute__((unused)) void* value) {
  return;
}

void ll_free(Node** head, void (vfree)(void*)) {
  if (!head) {
    return;
  }

  Node* cur = *head;
  *head = NULL;
  while (cur) {
    Node* next = cur->next;
    vfree(cur->value);
    free(cur);
    cur = next;
  }
}

Node* ll_reverse(Node* head, void* (vcopy)(void*)) {
  Node* new_head = NULL;

  while (head) {
    void* vnew = vcopy(head->value);
    if (!vnew) {
      ll_perror_exit(__FILE__, __LINE__, __FUNCTION__, "Error copying value!");
    }
    new_head = ll_add(new_head, vnew);
    head = head->next;
  }

  return new_head;
}

Node* ll_reverse_destructive(Node* head) {
  Node* nhead = NULL;
  Node* next = head;
  while (head) {
    nhead = ll_add(nhead, head->value);
    next = head->next;
    free(head);
    head = next;
  }

  return nhead;
}


Node* ll_from_string_array(char** values, size_t vcount) {
  Node *head = ll_new();

  for (size_t ii = 0; ii < vcount; ++ii) {
    head = ll_add(head, (void*)(values[ii]));
  }

  return ll_reverse_destructive(head);
}


void* ll_vcopy_noop(void* value) {
  return value;
}

void ll_visit(Node* head, void (*fvisit)(void*)) {
  while (head) {
    fvisit(head->value);
    head = head->next;
  }
}

/******************************************************************************/

void pprint_string_value(FILE* fp, void* value) {
  fprintf(fp, "\"%s\"", (char*)value);
}

void test_01() {
  Node *l1 = NULL; // ll_new();
  ll_pretty_print("emtpy", l1, pprint_string_value);
  l1 = ll_add(l1, "David");
  ll_pretty_print("has1 ", l1, pprint_string_value);
  l1 = ll_add(l1, "Kyle");
  ll_pretty_print("has2 ", l1, pprint_string_value);

  ASSERT(ll_len(l1) == 2, "Expected list to have a length of two");


  ll_free(&l1, ll_vfree_noop);
}

/*********************************************************************************/
char* ask_user_for_string(char *prompt) {
  size_t buff_size = 8192;
  char *buff = malloc(buff_size * sizeof(char));
  if (!buff) {
    ll_perror_exit(__FILE__, __LINE__, __FUNCTION__, "Error allocating memory to read string from user");
  }

  bzero(buff, buff_size);
  printf("%s: ", prompt);
  fflush(stdout);
  if (!fgets(buff, buff_size, stdin)) {
    ll_perror_exit(__FILE__, __LINE__, __FUNCTION__, "Error reading string from user");
    return NULL;
  }

  // NB: this is bad form
  *(strchr(buff,'\n')) = '\0';
  fprintf(stderr, "READ[%s]\n", buff);


  return buff;
}

void test_02 () {
  Node *l1 = ll_new();

  l1 = ll_add(l1, ask_user_for_string("How are you feeling?"));
  l1 = ll_add(l1, ask_user_for_string("How loud is the sun?"));
  l1 = ll_add(l1, ask_user_for_string("When is second breakfast?"));
  l1 = ll_add(l1, ask_user_for_string("How many Professor X's to an ocelot?"));

  printf("\n");
  ll_pretty_print("brought-to-you-by...", l1, pprint_string_value);

  ll_free(&l1, free);
}

void test_03 () {
  printf("%s(%d).%s: reverse a linked list\n", __FILE__, __LINE__, __FUNCTION__);
  Node* l1 = ll_new();
  l1 = ll_add(l1, "first");
  l1 = ll_add(l1, "second");
  l1 = ll_add(l1, "third");

  ll_pretty_print("l1", l1, pprint_string_value);
  Node* l2 = ll_reverse(l1, ll_vcopy_noop);
  ASSERT(ll_len(l1) == 3, "Expected list to have a length of 3");
  ll_pretty_print("l2", l2, pprint_string_value);

  ll_free(&l1, ll_vfree_noop);
  ll_free(&l2, ll_vfree_noop);
}

void test_04 () {
  printf("%s(%d).%s: add at the end O(n)...\n", __FILE__, __LINE__, __FUNCTION__);
  Node *l1 = ll_new();
  l1 = ll_add_end(l1, "first");
  l1 = ll_add_end(l1, "second");
  l1 = ll_add_end(l1, "third");
  ll_pretty_print("l1", l1, pprint_string_value);
  ASSERT(ll_len(l1) == 3, "Expected list to have a length of 3");
  ll_free(&l1, ll_vfree_noop);
}

void test_05 () {
  printf("%s(%d).%s: ll_nth_value...\n", __FILE__, __LINE__, __FUNCTION__);
  Node* l1 = ll_new();
  ASSERT(ll_len(l1) == 0, "Expected list to have a length of 0");
  l1 = ll_add_end(l1, "first");
  ASSERT(ll_len(l1) == 1, "Expected list to have a length of 1");
  l1 = ll_add_end(l1, "second");
  l1 = ll_add_end(l1, "third");
  l1 = ll_add_end(l1, "fourth");
  ASSERT(ll_len(l1) == 4, "Expected list to have a length of 4");

  ll_pretty_print("l1", l1, pprint_string_value);
  for (unsigned int ii = 0; ii < 4; ++ii) {
    char* val = (char*)ll_nth_value(l1, ii);
    if (!val) {
      printf("%s(%d).%s: FAILURE ll_nth_value not found for ii=%u\n", __FILE__, __LINE__, __FUNCTION__, ii);
      ASSERT(!!val, "Expected nth value to exist");
      break;
    }
    printf("%s(%d).%s: ll_nth_value(l1,%u) = %s\n", __FILE__, __LINE__, __FUNCTION__, ii, val);
  }

  char* val = (char*)ll_nth_value(l1, 9999);
  if (val != NULL) {
    printf("%s(%d).%s: FAILURE ll_nth_value found? ii=%u\n", __FILE__, __LINE__, __FUNCTION__, 9999);
  }

  ll_free(&l1, ll_vfree_noop);
}

void test_06 () {
  printf("%s(%d).%s: ll_from_array...\n", __FILE__, __LINE__, __FUNCTION__);
  char *strings[] = {
                     "first",
                     "second",
                     "third",
                     "fourth",
  };
  Node* l1 = ll_from_string_array(strings, sizeof(strings) / sizeof(char*));
  ll_pretty_print("l1 before", l1, pprint_string_value);
  ASSERT(ll_len(l1) == 4, "Expected length of 4");
  l1 = ll_pop(l1, ll_vfree_noop);
  l1 = ll_pop(l1, ll_vfree_noop);
  ll_pretty_print("l1 after ", l1, pprint_string_value);
  ASSERT(ll_len(l1) == 2, "Expected length of 2");
  ll_free(&l1, ll_vfree_noop);
}


static unsigned int num_visited;
void my_visit(void* value) {
  ++num_visited;
  printf("my_visit: value=%s\n", (char*)value);
}

void test_07 () {
  printf("%s(%d).%s: ll_from_array...\n", __FILE__, __LINE__, __FUNCTION__);
  char *strings[] = {
                     "first",
                     "second",
                     "third",
                     "fourth",
  };
  Node* l1 = ll_from_string_array(strings, sizeof(strings) / sizeof(char*));
  num_visited = 0;
  ll_visit(l1, my_visit);
  ASSERT(num_visited == 4, "Expected to visit 4 elements.");
  ll_free(&l1, ll_vfree_noop);
}

/*********************************************************************************/
int main (__attribute__((unused)) int argc, __attribute__((unused)) char** argv) {
  printf("Hello, Linked Lists\n");

  test_init();
  test_01();
  // NB: test_02 is interactive and reads from stdin
  /* test_02(); */
  test_03();
  test_04();
  test_05();
  test_06();
  test_07();
  test_report();
  return 0;
}
