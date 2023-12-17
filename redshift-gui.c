#include <gtk/gtk.h>

GtkWidget *entry;

static void apply_redshift_settings(GtkWidget *widget, gpointer data) {
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(entry));
    int temperature = atoi(text);
    
    char command[50];
    snprintf(command, sizeof(command), "redshift -O %d -b 1.0", temperature);
    system(command);
}

static void turn_off_redshift(GtkWidget *widget, gpointer data) {
    system("redshift -x");
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Redshift Controller");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Set the default size to be twice as big (width: 400, height: 200)
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_container_add(GTK_CONTAINER(window), box);

    entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box), entry, TRUE, TRUE, 0);

    GtkWidget *button1 = gtk_button_new_with_label("Apply Redshift Settings");
    g_signal_connect(button1, "clicked", G_CALLBACK(apply_redshift_settings), NULL);
    gtk_box_pack_start(GTK_BOX(box), button1, TRUE, TRUE, 0);

    GtkWidget *button2 = gtk_button_new_with_label("Turn Off Redshift");
    g_signal_connect(button2, "clicked", G_CALLBACK(turn_off_redshift), NULL);
    gtk_box_pack_start(GTK_BOX(box), button2, TRUE, TRUE, 0);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
