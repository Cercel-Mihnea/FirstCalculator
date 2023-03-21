#ifndef CALCULATOR3_H
#define CALCULATOR3_H
#include <gtk/gtk.h>

typedef struct calbutton
{
    char *value;
    GtkWidget *button;
}calbutton;

/*function prototype*/
gint delete_event(GtkWidget *window, GdkEvent *event, gpointer data);
void create_num_button(GtkWidget *box, GtkWidget *button, char* button_num);
void create_symbol_button(GtkWidget *box, GtkWidget *button, char* symbol);
void click_number(GtkWidget *widget, gpointer data);
void clear();
void submit(GtkWidget *widget, gpointer data);
void add(GtkWidget *widget, gpointer data);
void sub(GtkWidget *widget, gpointer data);
void mul(GtkWidget *widget, gpointer data);
void division(GtkWidget *widget, gpointer data);
void click_symbol(GtkWidget *widget, gpointer data);
float calculator(int first_number, int second_number, char data);
void change_sign();
#endif