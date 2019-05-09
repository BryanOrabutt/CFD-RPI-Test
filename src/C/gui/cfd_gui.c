#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>

/* Setup GTK Object handles for each widget */

//global settings check boxes
GtkWidget *GEN_CB_h;
GtkWidget *GMode_CB_h;
GtkWidget *Neg_Pol_CB_h;
GtkWidget *Internal_AGND_CB_h;

//global settings combo boxes/text boxes
GtkWidget *Nowlin_Mode_Menu_h;
GtkWidget *Nowlin_Delay_Menu_h;
GtkWidget *Test_Point_Menu_h;
GtkWidget *Lockout_Mode_Menu_h;
GtkWidget *Lockout_DAC_Box_h;
GtkWidget *AGND_Trim_Menu_h;

//channel enable checkboxes
GtkWidget *Channel0_EN_CB_h;
GtkWidget *Channel1_EN_CB_h;
GtkWidget *Channel2_EN_CB_h;
GtkWidget *Channel3_EN_CB_h;
GtkWidget *Channel4_EN_CB_h;
GtkWidget *Channel5_EN_CB_h;
GtkWidget *Channel6_EN_CB_h;
GtkWidget *Channel7_EN_CB_h;
GtkWidget *Channel8_EN_CB_h;
GtkWidget *Channel9_EN_CB_h;
GtkWidget *Channel10_EN_CB_h;
GtkWidget *Channel11_EN_CB_h;
GtkWidget *Channel12_EN_CB_h;
GtkWidget *Channel13_EN_CB_h;
GtkWidget *Channel14_EN_CB_h;
GtkWidget *Channel15_EN_CB_h;

//leading edge DAC text boxes
GtkWidget *Channel0_LE_DAC_Box_h;
GtkWidget *Channel1_LE_DAC_Box_h;
GtkWidget *Channel2_LE_DAC_Box_h;
GtkWidget *Channel3_LE_DAC_Box_h;
GtkWidget *Channel4_LE_DAC_Box_h;
GtkWidget *Channel5_LE_DAC_Box_h;
GtkWidget *Channel6_LE_DAC_Box_h;
GtkWidget *Channel7_LE_DAC_Box_h;
GtkWidget *Channel8_LE_DAC_Box_h;
GtkWidget *Channel9_LE_DAC_Box_h;
GtkWidget *Channel10_LE_DAC_Box_h;
GtkWidget *Channel11_LE_DAC_Box_h;
GtkWidget *Channel12_LE_DAC_Box_h;
GtkWidget *Channel13_LE_DAC_Box_h;
GtkWidget *Channel14_LE_DAC_Box_h;
GtkWidget *Channel15_LE_DAC_Box_h;

//config button
GtkWidget *Confiure_Button_h;

/* Callback functions */

void on_GEN_CB_toggled()
{
	printf("GEN toggled\n");
}

void on_GMode_CB_toggled()
{
	printf("GMode toggled\n");
}

void on_Neg_Pol_CB_toggled()
{
	printf("Neg pol toggled\n");
}

void on_Internal_AGND_CB_toggled()
{
	printf("Internal AGND toggled\n");
}

void on_Nowlin_Mode_Menu_changed()
{
	printf("Nowlin mode menu changed\t");
	GtkComboBoxText* delaybox = GTK_COMBO_BOX_TEXT(Nowlin_Delay_Menu_h);
	GtkComboBoxText* modebox = GTK_COMBO_BOX_TEXT(Nowlin_Mode_Menu_h);
	
	gchar* mode = gtk_combo_box_text_get_active_text(modebox);
	g_printf("%s\n", mode);

	gtk_combo_box_text_remove_all(delaybox);

	gchar* tmp = "Short";
	int scale = 1;

	if(g_strcmp0(tmp, mode) != 0)
		scale = 12;

	for(int i = 0; i < 16; i++)
	{
		gchar str[4];
		g_snprintf(str, 4, "%d", (i+1)*scale);
		gtk_combo_box_text_append_text(delaybox, str);
	}	


}

void on_Nowlin_Delay_Menu_changed()
{
	printf("Nowlin delay menu changed\n");
}

void on_Test_Point_Menu_changed()
{
	printf("Test point menu changed\n");
}

void on_Lockout_Mode_Menu_changed()
{
	printf("Lockout mode menu changed\n");
}

void on_lockout_dac_deleted_text()
{
	printf("Lockout DAC textbox: text deleted\n");
}

void on_lockout_dac_inserted_text()
{
	printf("Lockout DAC textbox: text inserted\n");
}

void on_AGND_Trim_Menu_changed()
{
	printf("AGND trim menu changed\n");
}

void channel_enable_event(int channel)
{
	printf("Channel%i enable toggled\n", channel);
}

void on_Channel0_EN_CB_toggled()
{
	channel_enable_event(0);
}

void on_Channel1_EN_CB_toggled()
{
	channel_enable_event(1);
}

void on_Channel2_EN_CB_toggled()
{
	channel_enable_event(2);
}

void on_Channel3_EN_CB_toggled()
{
	channel_enable_event(3);
}

void on_Channel4_EN_CB_toggled()
{
	channel_enable_event(4);
}

void on_Channel5_EN_CB_toggled()
{
	channel_enable_event(5);
}

void on_Channel6_EN_CB_toggled()
{
	channel_enable_event(6);
}

void on_Channel7_EN_CB_toggled()
{
	channel_enable_event(7);
}

void on_Channel8_EN_CB_toggled()
{
	channel_enable_event(8);
}

void on_Channel9_EN_CB_toggled()
{
	channel_enable_event(9);
}

void on_Channel10_EN_CB_toggled()
{
	channel_enable_event(10);
}

void on_Channel11_EN_CB_toggled()
{
	channel_enable_event(11);
}

void on_Channel12_EN_CB_toggled()
{
	channel_enable_event(12);
}

void on_Channel13_EN_CB_toggled()
{
	channel_enable_event(13);
}

void on_Channel14_EN_CB_toggled()
{
	channel_enable_event(14);
}

void on_Channel15_EN_CB_toggled()
{
	channel_enable_event(15);
}

void channel_text_deleted(int channel)
{
	printf("Channel%d DAC box: text deleted\n", channel);
}

void channel_text_inserted(int channel)
{
	printf("Channel%d DAC box: text inserted\n", channel);
}

void on_ch0_dac_deleted_text()
{
	channel_text_deleted(0);
}

void on_ch0_dac_inserted_text()
{
	channel_text_inserted(0);
}

void on_ch1_dac_deleted_text()
{
	channel_text_deleted(1);
}

void on_ch1_dac_inserted_text()
{
	channel_text_inserted(1);
}

void on_ch2_dac_deleted_text()
{
	channel_text_deleted(2);
}

void on_ch2_dac_inserted_text()
{
	channel_text_inserted(2);
}

void on_ch3_dac_deleted_text()
{
	channel_text_deleted(3);
}

void on_ch3_dac_inserted_text()
{
	channel_text_inserted(3);
}

void on_ch4_dac_deleted_text()
{
	channel_text_deleted(4);
}

void on_ch4_dac_inserted_text()
{
	channel_text_inserted(4);
}

void on_ch5_dac_deleted_text()
{
	channel_text_deleted(5);
}

void on_ch5_dac_inserted_text()
{
	channel_text_inserted(5);
}

void on_ch6_dac_deleted_text()
{
	channel_text_deleted(6);
}

void on_ch6_dac_inserted_text()
{
	channel_text_inserted(6);
}

void on_ch7_dac_deleted_text()
{
	channel_text_deleted(7);
}

void on_ch7_dac_inserted_text()
{
	channel_text_inserted(7);
}

void on_ch8_dac_deleted_text()
{
	channel_text_deleted(8);
}

void on_ch8_dac_inserted_text()
{
	channel_text_inserted(8);
}

void on_ch9_dac_deleted_text()
{
	channel_text_deleted(9);
}

void on_ch9_dac_inserted_text()
{
	channel_text_inserted(9);
}

void on_ch10_dac_deleted_text()
{
	channel_text_deleted(10);
}

void on_ch10_dac_inserted_text()
{
	channel_text_inserted(10);
}

void on_ch11_dac_deleted_text()
{
	channel_text_deleted(11);
}

void on_ch11_dac_inserted_text()
{
	channel_text_inserted(11);
}

void on_ch12_dac_deleted_text()
{
	channel_text_deleted(12);
}

void on_ch12_dac_inserted_text()
{
	channel_text_inserted(12);
}

void on_ch13_dac_deleted_text()
{
	channel_text_deleted(13);
}

void on_ch13_dac_inserted_text()
{
	channel_text_inserted(13);
}

void on_ch14_dac_deleted_text()
{
	channel_text_deleted(14);
}

void on_ch14_dac_inserted_text()
{
	channel_text_inserted(14);
}

void on_ch15_dac_deleted_text()
{
	channel_text_deleted(15);
}

void on_ch15_dac_inserted_text()
{
	channel_text_inserted(15);
}

void on_Configure_Button_clicked()
{
	printf("Configure button clicked\n");
}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}


int main(int argc, char *argv[])
{
    GtkBuilder      *builder;
    GtkWidget       *window;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "CFD.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));

	GEN_CB_h = GTK_WIDGET(gtk_builder_get_object(builder, "GEN_CB"));
	GMode_CB_h = GTK_WIDGET(gtk_builder_get_object(builder, "GMode_CB"));
	Neg_Pol_CB_h = GTK_WIDGET(gtk_builder_get_object(builder, "Neg_Pol_CB"));
	Internal_AGND_CB_h = GTK_WIDGET(gtk_builder_get_object(builder, "Internal_AGND_CB"));

	Nowlin_Mode_Menu_h = GTK_WIDGET(gtk_builder_get_object(builder, "Nowlin_Mode_Menu"));
	Nowlin_Delay_Menu_h = GTK_WIDGET(gtk_builder_get_object(builder, "Nowlin_Delay_Menu"));
	Test_Point_Menu_h = GTK_WIDGET(gtk_builder_get_object(builder, "Test_Point_Menu"));
	Lockout_Mode_Menu_h = GTK_WIDGET(gtk_builder_get_object(builder, "Lockout_Mode_Menu"));
	Lockout_DAC_Box_h = GTK_WIDGET(gtk_builder_get_object(builder, "Lockout_DAC_Box"));
	AGND_Trim_Menu_h = GTK_WIDGET(gtk_builder_get_object(builder, "AGND_Trim_Menu"));


	Channel0_EN_CB_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel0_EN_CB"));
	Channel0_LE_DAC_Box_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel0_LE_DAC_Box"));

	Channel1_EN_CB_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel1_EN_CB"));
	Channel1_LE_DAC_Box_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel1_LE_DAC_Box"));

	Channel2_EN_CB_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel2_EN_CB"));
	Channel2_LE_DAC_Box_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel2_LE_DAC_Box"));

	Channel3_EN_CB_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel3_EN_CB"));
	Channel3_LE_DAC_Box_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel3_LE_DAC_Box"));

	Channel4_EN_CB_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel4_EN_CB"));
	Channel4_LE_DAC_Box_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel4_LE_DAC_Box"));

	Channel5_EN_CB_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel5_EN_CB"));
	Channel5_LE_DAC_Box_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel5_LE_DAC_Box"));

	Channel6_EN_CB_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel6_EN_CB"));
	Channel6_LE_DAC_Box_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel6_LE_DAC_Box"));

	Channel7_EN_CB_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel7_EN_CB"));
	Channel7_LE_DAC_Box_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel7_LE_DAC_Box"));

	Channel8_EN_CB_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel8_EN_CB"));
	Channel8_LE_DAC_Box_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel8_LE_DAC_Box"));

	Channel9_EN_CB_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel9_EN_CB"));
	Channel9_LE_DAC_Box_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel9_LE_DAC_Box"));

	Channel10_EN_CB_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel10_EN_CB"));
	Channel10_LE_DAC_Box_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel10_LE_DAC_Box"));

	Channel11_EN_CB_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel11_EN_CB"));
	Channel11_LE_DAC_Box_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel11_LE_DAC_Box"));

	Channel12_EN_CB_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel12_EN_CB"));
	Channel12_LE_DAC_Box_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel12_LE_DAC_Box"));

	Channel13_EN_CB_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel13_EN_CB"));
	Channel13_LE_DAC_Box_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel13_LE_DAC_Box"));

	Channel14_EN_CB_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel14_EN_CB"));
	Channel14_LE_DAC_Box_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel14_LE_DAC_Box"));

	Channel15_EN_CB_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel15_EN_CB"));
	Channel15_LE_DAC_Box_h = GTK_WIDGET(gtk_builder_get_object(builder, "Channel15_LE_DAC_Box"));


    gtk_builder_connect_signals(builder, NULL);
    printf("connect returned\n");

    g_object_unref(builder);
    printf("unref returned\n");

    gtk_widget_show(window);
    printf("show returned\n");
    gtk_main();

    return 0;
}
