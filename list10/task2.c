#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

/* jak komus sie chce to niech napisze algorytm komputera - funkcja "moveComputer" */

/* deklaracje funkcji */
void xWinner();
void oWinner();
void remisWinner();
void computer (GtkWidget *widget, gpointer window);
void member (GtkWidget *widget, gpointer window);
void clickedButton(GtkWidget *widget, GtkWidget **buttons);
GtkWidget *moveComputer(GtkWidget **buttons);
void whoWon(GtkWidget **buttons);
void createTicTacBoard(int n);

int main(int argc, char *argv[]) {

    char *words = "Wybierz prowadzacego";
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *container = gtk_vbox_new(FALSE, 1);
    GtkWidget *label = gtk_label_new(words);

    /* deklaracja przyciskow */
    GtkWidget *button = gtk_button_new_with_label("Komputer");
    GtkWidget *button2 = gtk_button_new_with_label("Uzytkownik");

    /* podstawowe ustawienia GTK */
    gtk_window_set_title(GTK_WINDOW(window), "Kolko i krzyzyk");
    gtk_window_set_default_size(GTK_WINDOW(window), 220, 120);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_add(GTK_CONTAINER(window), container);

    /* wyswietlenie tekstu */
    gtk_container_add(GTK_CONTAINER(container), label);

    /* ustawienie przyciskow */
    gtk_container_set_border_width(GTK_CONTAINER(window), 13);
    gtk_box_pack_start(GTK_BOX(container), button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(container), button2, TRUE, TRUE, 0);

    /* sygnaly */
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(computer), (gpointer)window);
    g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(member), (gpointer)window);

    /* koncowka */
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

void computer(GtkWidget *widget, gpointer window) {
    gtk_widget_hide_all(GTK_WIDGET(window));
    createTicTacBoard(0);
}

void member(GtkWidget *widget, gpointer window) {
    gtk_widget_hide_all(GTK_WIDGET(window));
    createTicTacBoard(1);
}

void clickedButton(GtkWidget *widget, GtkWidget **buttons) {
    if(strlen(gtk_button_get_label(GTK_BUTTON(widget))) != 1) {
        gtk_button_set_label(GTK_BUTTON(widget), "X");

        GtkWidget *i = 0;
        whoWon(buttons);

        while(1) {
            i = moveComputer(buttons);
            if(strlen(gtk_button_get_label(GTK_BUTTON(i))) != 1) {
                gtk_button_set_label(GTK_BUTTON(i), "O");
                break;
            }
        }
    }
    whoWon(buttons);
}

GtkWidget *moveComputer(GtkWidget **buttons) {
    return buttons[rand() % 9];
}

void whoWon(GtkWidget **buttons) {

    for(int i = 0; i < 3; i++) {
        /* warunki w pionie dla X */
        if((strcmp(gtk_button_get_label(GTK_BUTTON(buttons[i])), "X") == 0 ) && (strcmp(gtk_button_get_label(GTK_BUTTON(buttons[i + 3])), "X") == 0 ) &&
            (strcmp(gtk_button_get_label(GTK_BUTTON(buttons[i + 6])), "X") == 0)) xWinner();
        /* warunki w pionie dla O */
        if((strcmp(gtk_button_get_label(GTK_BUTTON(buttons[i])), "O") == 0 ) && (strcmp(gtk_button_get_label(GTK_BUTTON(buttons[i + 3])), "O") == 0 ) &&
           (strcmp(gtk_button_get_label(GTK_BUTTON(buttons[i + 6])), "O") == 0)) oWinner();
    }

    for(int i = 0; i < 9; i += 3) {
        /* warunki w poziomie dla X */
        if((strcmp(gtk_button_get_label(GTK_BUTTON(buttons[i])), "X") == 0 ) && (strcmp(gtk_button_get_label(GTK_BUTTON(buttons[i + 1])), "X") == 0 ) &&
            (strcmp(gtk_button_get_label(GTK_BUTTON(buttons[i + 2])), "X") == 0)) xWinner();
        /* warunki w poziomie dla O */
        if((strcmp(gtk_button_get_label(GTK_BUTTON(buttons[i])), "O") == 0 ) && (strcmp(gtk_button_get_label(GTK_BUTTON(buttons[i + 1])), "O") == 0 ) &&
           (strcmp(gtk_button_get_label(GTK_BUTTON(buttons[i + 2])), "O") == 0)) oWinner();
    }

    /* sprawdzanie warunkow dla przekatnych */
    if((strcmp(gtk_button_get_label(GTK_BUTTON(buttons[0])), "X") == 0 ) && (strcmp(gtk_button_get_label(GTK_BUTTON(buttons[4])), "X") == 0 ) &&
        (strcmp(gtk_button_get_label(GTK_BUTTON(buttons[8])), "X") == 0)) xWinner();
        /* warunki dla O */
    if((strcmp(gtk_button_get_label(GTK_BUTTON(buttons[0])), "O") == 0 ) && (strcmp(gtk_button_get_label(GTK_BUTTON(buttons[4])), "O") == 0 ) &&
        (strcmp(gtk_button_get_label(GTK_BUTTON(buttons[8])), "O") == 0)) oWinner();
    /* --- w druga strone --- */
    if((strcmp(gtk_button_get_label(GTK_BUTTON(buttons[2])), "X") == 0 ) && (strcmp(gtk_button_get_label(GTK_BUTTON(buttons[4])), "X") == 0 ) &&
       (strcmp(gtk_button_get_label(GTK_BUTTON(buttons[6])), "X") == 0)) xWinner();
        /* warunki dla O */
    if((strcmp(gtk_button_get_label(GTK_BUTTON(buttons[2])), "O") == 0 ) && (strcmp(gtk_button_get_label(GTK_BUTTON(buttons[4])), "O") == 0 ) &&
        (strcmp(gtk_button_get_label(GTK_BUTTON(buttons[6])), "O") == 0)) oWinner();

    int x, y = 1;
    /* warunek jezeli sa wypelnione pole */
    for(x = 0; x < 9; x++)
        if(strlen(gtk_button_get_label(GTK_BUTTON(buttons[x]))) != 1) y = 0;

    if(y != 0)
        remisWinner();

}

void xWinner() {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget * dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Zwyciezyl uzytkownik [X]");
    gtk_window_set_title(GTK_WINDOW(dialog), "Wygrana!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    exit(0);
}

void oWinner() {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget * dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Zwyciezyl komputer [O]");
    gtk_window_set_title(GTK_WINDOW(dialog), "Wygrana!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    exit(0);
}

void remisWinner() {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget * dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Nikt nie wygral. Remis [XO]");
    gtk_window_set_title(GTK_WINDOW(dialog), "Remis!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    exit(0);
}

void createTicTacBoard(int n) {

    GtkWidget *button[9];
    GtkWidget *table = gtk_table_new(3, 3, TRUE);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    int i, j;

    /* podstawowe ustawienia GTK */
    gtk_window_set_title(GTK_WINDOW(window), "Gra Kolko i krzyzyk");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    /* tabelka */
    gtk_table_set_row_spacings(GTK_TABLE(table), 4);
    gtk_table_set_col_spacings(GTK_TABLE(table), 4);

    for (i = 0; i < 9; i++) {
        button[i] = gtk_button_new_with_label("");
        if(n == 0 && i == 4) button[4] = gtk_button_new_with_label("O");
    }

    for(i = 0; i < 3; i++ )
        for(j = 0; j < 3; j++)
            gtk_table_attach_defaults(GTK_TABLE(table), button[(j * 3) + i], i, i + 1, j, j + 1);
    gtk_container_add(GTK_CONTAINER(window), table);

    /* sygnaly */
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    for(i = 0; i < 9; i++)
        g_signal_connect(G_OBJECT(button[i]), "clicked", G_CALLBACK(clickedButton), (gpointer)button);

    /* koncowka */
    gtk_widget_show_all(window);
    gtk_main();
}
