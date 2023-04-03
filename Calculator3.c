#include "Calculator3.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

GtkWidget *entry;
GtkEntryBuffer *buffer;

float first_number = -1.0;
float second_number = -1.0;
int first_number_check = 0;
int second_number_check = 0;
int has_press_number = 0;
int has_press_symbol = 0;
int need_clear = 0;
char symbol;
int negative = 0;
int entry_int = 0;

static void
activate (GtkApplication *app)
{
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_application (GTK_WINDOW (window), app);
    gtk_window_set_title (GTK_WINDOW (window), "Calculator");
    gtk_window_set_default_size (GTK_WINDOW (window), 400, 400);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(GTK_WINDOW (window), vbox);
    gtk_widget_show(vbox);

    GtkWidget *hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
    gtk_box_insert_child_after(GTK_BOX(vbox), hbox1,NULL);

    
    buffer =gtk_entry_buffer_new("0", -1);
    entry = gtk_entry_new_with_buffer(buffer);
    gtk_editable_set_editable(GTK_EDITABLE(entry), FALSE);
    gtk_widget_set_direction(entry, GTK_TEXT_DIR_RTL);
    gtk_entry_set_alignment(GTK_ENTRY(entry), 1);
    gtk_widget_set_size_request(entry, 250, 100);  
    gtk_box_append(GTK_BOX(hbox1), entry);
    gtk_widget_show(entry);

    GtkWidget *button = gtk_button_new_with_label("C");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(clear), NULL);
    gtk_box_append(GTK_BOX(hbox1), button);
    gtk_widget_set_size_request(button, 50, 100);  
    gtk_widget_show(button);
    button = gtk_button_new_with_label("-/+");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(change_sign), NULL);
    gtk_box_append(GTK_BOX(hbox1), button);
    gtk_widget_set_size_request(button, 50, 100);  
    gtk_widget_show(button);
    button = gtk_button_new_with_label("<=");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(back), NULL);
    gtk_box_append(GTK_BOX(hbox1), button);
    gtk_widget_set_size_request(button, 50, 100);  
    gtk_widget_show(button);
    gtk_widget_show(hbox1);

    GtkWidget *hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_box_insert_child_after(GTK_BOX(vbox), hbox2, hbox1);
    

    gtk_widget_show(button);
    gtk_widget_show(hbox2);

    GtkWidget *hbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_box_insert_child_after(GTK_BOX(vbox), hbox3, hbox1);
    create_num_button(hbox3, button, "7");
    create_num_button(hbox3, button, "8");
    create_num_button(hbox3, button, "9");
    create_symbol_button(hbox3, button, "/");
    gtk_widget_show(hbox3);

    GtkWidget *hbox4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_box_insert_child_after(GTK_BOX(vbox), hbox4, hbox3);
    create_num_button(hbox4, button, "4");
    create_num_button(hbox4, button, "5");
    create_num_button(hbox4, button, "6");
    create_symbol_button(hbox4, button, "*");
    gtk_widget_show(hbox4);

    GtkWidget *hbox5 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_box_insert_child_after(GTK_BOX(vbox), hbox5, hbox4);
    create_num_button(hbox5, button, "1");
    create_num_button(hbox5, button, "2");
    create_num_button(hbox5, button, "3");
    create_symbol_button(hbox5, button, "-");
    gtk_widget_show(hbox5);

    GtkWidget *hbox6 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_box_insert_child_after(GTK_BOX(vbox), hbox6, hbox5);
    create_symbol_button(hbox6, button, "%");
    create_num_button(hbox6, button, "0");

    button = gtk_button_new_with_label("=");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(submit), NULL);
    gtk_box_append(GTK_BOX(hbox6), button);
    gtk_widget_set_size_request(button, 100, 90);
    gtk_widget_show(button);

    create_symbol_button(hbox6, button, "+");
    gtk_widget_show(hbox6);

  gtk_widget_show(window);
}
int main (int argc, char *argv[])
{

    GtkApplication *app = gtk_application_new ("calculator.gtk", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    int status = g_application_run (G_APPLICATION (app), argc, argv);
  
    g_object_unref (app);

  return status;
}

void create_num_button(GtkWidget *box, GtkWidget *button, char* button_num)
{
    button = gtk_button_new_with_label(button_num);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(click_number), (gpointer)button_num);
    
    gtk_box_append(GTK_BOX(box), button);
    gtk_widget_set_size_request(button, 100, 90);
    gtk_widget_show(button);
}
void click_number(GtkWidget *widget, gpointer data)
{
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  if(need_clear)
  {
    gtk_entry_buffer_set_text(buffer, "0", -1);
    entry_int = 0;
    need_clear = 0;
  }

  const char* button_num = (const char*) data;
  
  
  if(entry_int == 0)
   {
     gtk_entry_buffer_set_text(buffer, button_num, -1);
     entry_int = 1;
   }
  else
  {
    const char* new_text = gtk_entry_buffer_get_text(buffer);
    gtk_entry_buffer_insert_text(buffer, strlen(new_text), button_num, -1);
  }
  has_press_number = 1;
}

void create_symbol_button(GtkWidget *box, GtkWidget *button, char* symbol)
{
  button = gtk_button_new_with_label(symbol);
  g_signal_connect(button, "clicked", G_CALLBACK(click_symbol), (gpointer)symbol);
  gtk_box_append(GTK_BOX(box), button);
  gtk_widget_set_size_request(button, 100, 90);
  gtk_widget_show(button);
}

void clear()
{ 
  GtkEntryBuffer *buffer =gtk_entry_get_buffer(GTK_ENTRY(entry));
  gtk_entry_buffer_set_text(buffer, "0", -1);
  first_number = 0;
  second_number = 0;
  first_number_check = 0;
  second_number_check = 0;
  has_press_number = 0;
  has_press_symbol = 0;
  need_clear = 0;
  symbol = '+';
  entry_int = 0;
}

void click_symbol(GtkWidget *widgfet, gpointer data)
{
  symbol = *(char*)data;
  if(has_press_number == 1 && has_press_symbol == 0 && first_number_check == 0)
    {
      first_number = atoi(gtk_entry_buffer_get_text(buffer)) ;
      has_press_number = 0;
      first_number_check = 1;
      second_number_check = 0;
      
    }
    else if(has_press_number == 1 && has_press_symbol == 1)
    {
      second_number = atoi(gtk_entry_buffer_get_text(buffer));
      first_number = calculator(first_number, second_number, symbol);
      second_number_check = 1;
      first_number_check = 0;
    }
  has_press_symbol = 1;
  const char* new_text = gtk_entry_buffer_get_text(buffer);
  gtk_entry_buffer_insert_text(buffer, strlen(new_text), (char*)data, -1);
  need_clear = 1;
}

void submit(GtkWidget *widget, gpointer data)
{
  if(has_press_number == 1 && has_press_symbol == 1)
  {
    second_number = atoi(gtk_entry_buffer_get_text(buffer));
    first_number = calculator(first_number, second_number, symbol);
  }

  char* result_string = malloc(sizeof(char) * 10);
  memset(result_string, 0, 10);
  sprintf(result_string, "%.2f", first_number); 
  gtk_entry_buffer_set_text(buffer, result_string, -1);
}

float calculator(int first_number, int second_number, char symbol)
{
    float result;
    float per = 100;
    switch(symbol)
    {
      case '+':
        result = first_number + (second_number*1.0);
        break;
      case '-':
        result = first_number - (second_number*1.0);
        break;
      case '/':
        result = first_number / (second_number*1.0);
        break;
      case '*':
        result = first_number * (second_number*1.0);
        break;
      case '%':
        result =  first_number * (second_number*1.0) / per;
        break;
    }

  return result;
}
void change_sign()
{
  char* result_string = malloc(sizeof(char) * 10);
  memset(result_string, 0, 10);
    if(entry_int == 0)
    {
      if(negative == 0)
      {
        negative = 1;
        gtk_entry_buffer_set_text(buffer, "-", -1);
      }
      else
      {
        negative = 0;
        gtk_entry_buffer_set_text(buffer, "+" , -1);
      }
  entry_int = 1;
    }
    else if(has_press_number == 1 && first_number_check == 0)
    {
      first_number = atoi(gtk_entry_buffer_get_text(buffer));
      printf("\n%f\n", first_number);
      first_number = 0 - (first_number*1.0);
      sprintf(result_string, "%.0f", first_number);
      gtk_entry_buffer_set_text(buffer, result_string, -1);
    }
    else if(has_press_number == 1 && first_number_check == 1 && second_number_check == 0)
    {
      second_number = atoi(gtk_entry_buffer_get_text(buffer));
      printf("\n%f\n", second_number);
      second_number = 0 - (second_number*1.0);
      sprintf(result_string, "%.0f", second_number);
      gtk_entry_buffer_set_text(buffer, result_string, -1);
    }
}
void back()
{
  guint length = gtk_entry_buffer_get_length(buffer) - 1;
  gtk_entry_buffer_delete_text(buffer, length, 1);
}