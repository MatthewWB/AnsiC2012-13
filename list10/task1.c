#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

typedef struct {
    GtkWidget *input;
    GtkWidget *label;
} struktura;

gchar* lacz(gchar *a, char *b);
void czynnik(GtkWidget *wid, struktura *tmp);


int main (int argc, char *argv[]){
    gtk_init(&argc, &argv);

    GtkWidget *windows = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size( GTK_WINDOW( windows ), 200, 50);

    gtk_window_set_position( GTK_WINDOW( windows ), GTK_WIN_POS_CENTER );
    gtk_window_set_title( GTK_WINDOW( windows ), "Rozklad na czynniki pierwsze" );
    GtkWidget *mainK = gtk_vbox_new( FALSE, 1 );
    gtk_container_add( GTK_CONTAINER( windows ), mainK );
    GtkWidget *kontener = gtk_hbox_new( FALSE, 1 );
    gtk_box_pack_start( GTK_BOX(mainK), kontener, TRUE, FALSE, 0 );
    GtkWidget * input = gtk_entry_new();
    gtk_box_pack_start( GTK_BOX( kontener ), input, TRUE, TRUE, 0 );
    GtkWidget *przycisk = gtk_button_new_with_label( "Licz" );
    gtk_box_pack_start( GTK_BOX( kontener ), przycisk, TRUE, TRUE, 0 );
    GtkWidget *kontenerBottom = gtk_vbox_new( FALSE, 1 );
    gtk_box_pack_start( GTK_BOX( mainK ), kontenerBottom, TRUE, TRUE, 0 );

    GtkWidget *etykieta = gtk_label_new( "" );
    gtk_box_pack_start( GTK_BOX( kontenerBottom ), etykieta, TRUE, TRUE, 0 );

    struktura tmp;
    tmp.input = input;
    tmp.label = etykieta;

    g_signal_connect( G_OBJECT( windows ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );
    g_signal_connect( przycisk, "clicked", G_CALLBACK(czynnik), (gpointer)&tmp);

    gtk_widget_show_all( windows );
    gtk_main();

    return 0;
}

gchar* lacz(gchar *i, char *j){
    gchar *laczenie = malloc((strlen(i) + strlen(j) +5 )*sizeof*laczenie);
    strcpy(laczenie, i);
    strcat(laczenie, " ");
    strcat(laczenie, j);
    return laczenie;
}

void czynnik(GtkWidget *wid, struktura *tmp){
    gtk_label_set_text(GTK_LABEL( tmp->label ), "");
    gchar *text = gtk_entry_get_text(GTK_ENTRY(tmp->input));

    int k = 2, liczba = atoi(text);
     while(liczba > 1){
        if(liczba % k == 0){
            liczba = liczba / k;
            char *temp = malloc(10 * sizeof * temp);
            sprintf(temp, "%d", k);
            gtk_label_set_text(GTK_LABEL(tmp->label), lacz(gtk_label_get_text(GTK_LABEL(tmp->label)), temp));
            continue;
        }
        k++;
    }
}
