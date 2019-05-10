#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <cfd_rpi.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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

//Save & load interface handles
GtkWidget *Save_File_Box_h;
GtkWidget *Load_File_Box_h;
GtkWidget *Save_File_Button_h;

//config button
GtkWidget *Confiure_Button_h;

/* Global variables */
char leading_edge_dac[CHANNELS]; //value to write to individual channel
char gmode;
char neg_pol;
char gen;
char int_agnd_en;
char agnd_trim;
char nowlin_mode;
char nowlin_delay;
char lockout_mode;
char test_point_sel;
char lockout_dac;
char ch_en[CHANNELS]; //individual channel enable flags



/* Callback functions */

void on_GEN_CB_toggled()
{
	printf("gen_cb = %p\n", GEN_CB_h);
	GtkToggleButton* gen_cb = GTK_TOGGLE_BUTTON(GEN_CB_h);
	gen = (gtk_toggle_button_get_active(gen_cb)) ? 1:0;
	printf("GEN toggled: %s\n", (gen) ? "ON":"OFF");
}

void on_GMode_CB_toggled()
{
	GtkToggleButton* gmode_cb = GTK_TOGGLE_BUTTON(GMode_CB_h);

	gmode = (gtk_toggle_button_get_active(gmode_cb)) ? 1:0;
	
	if(gmode)
	{
			gtk_entry_set_text(GTK_ENTRY(Channel1_LE_DAC_Box_h), "N/A");
			gtk_editable_set_editable(GTK_EDITABLE(Channel1_LE_DAC_Box_h), 0);
			gtk_widget_set_can_focus(Channel1_LE_DAC_Box_h, 0);
			gtk_entry_set_text(GTK_ENTRY(Channel2_LE_DAC_Box_h), "N/A");
			gtk_editable_set_editable(GTK_EDITABLE(Channel2_LE_DAC_Box_h), 0);
			gtk_widget_set_can_focus(Channel2_LE_DAC_Box_h, 0);
			gtk_entry_set_text(GTK_ENTRY(Channel3_LE_DAC_Box_h), "N/A");
			gtk_editable_set_editable(GTK_EDITABLE(Channel3_LE_DAC_Box_h), 0);
			gtk_widget_set_can_focus(Channel3_LE_DAC_Box_h, 0);
			gtk_entry_set_text(GTK_ENTRY(Channel4_LE_DAC_Box_h), "N/A");
			gtk_editable_set_editable(GTK_EDITABLE(Channel4_LE_DAC_Box_h), 0);
			gtk_widget_set_can_focus(Channel4_LE_DAC_Box_h, 0);
			gtk_entry_set_text(GTK_ENTRY(Channel5_LE_DAC_Box_h), "N/A");
			gtk_editable_set_editable(GTK_EDITABLE(Channel5_LE_DAC_Box_h), 0);
			gtk_widget_set_can_focus(Channel5_LE_DAC_Box_h, 0);
			gtk_entry_set_text(GTK_ENTRY(Channel6_LE_DAC_Box_h), "N/A");
			gtk_editable_set_editable(GTK_EDITABLE(Channel6_LE_DAC_Box_h), 0);
			gtk_widget_set_can_focus(Channel6_LE_DAC_Box_h, 0);
			gtk_entry_set_text(GTK_ENTRY(Channel7_LE_DAC_Box_h), "N/A");
			gtk_editable_set_editable(GTK_EDITABLE(Channel7_LE_DAC_Box_h), 0);
			gtk_widget_set_can_focus(Channel7_LE_DAC_Box_h, 0);
			gtk_entry_set_text(GTK_ENTRY(Channel8_LE_DAC_Box_h), "N/A");
			gtk_editable_set_editable(GTK_EDITABLE(Channel8_LE_DAC_Box_h), 0);
			gtk_widget_set_can_focus(Channel8_LE_DAC_Box_h, 0);
			gtk_entry_set_text(GTK_ENTRY(Channel9_LE_DAC_Box_h), "N/A");
			gtk_editable_set_editable(GTK_EDITABLE(Channel9_LE_DAC_Box_h), 0);
			gtk_widget_set_can_focus(Channel9_LE_DAC_Box_h, 0);
			gtk_entry_set_text(GTK_ENTRY(Channel10_LE_DAC_Box_h), "N/A");
			gtk_editable_set_editable(GTK_EDITABLE(Channel10_LE_DAC_Box_h), 0);
			gtk_widget_set_can_focus(Channel10_LE_DAC_Box_h, 0);
			gtk_entry_set_text(GTK_ENTRY(Channel11_LE_DAC_Box_h), "N/A");
			gtk_editable_set_editable(GTK_EDITABLE(Channel11_LE_DAC_Box_h), 0);
			gtk_widget_set_can_focus(Channel11_LE_DAC_Box_h, 0);
			gtk_entry_set_text(GTK_ENTRY(Channel12_LE_DAC_Box_h), "N/A");
			gtk_editable_set_editable(GTK_EDITABLE(Channel12_LE_DAC_Box_h), 0);
			gtk_widget_set_can_focus(Channel12_LE_DAC_Box_h, 0);
			gtk_entry_set_text(GTK_ENTRY(Channel13_LE_DAC_Box_h), "N/A");
			gtk_editable_set_editable(GTK_EDITABLE(Channel13_LE_DAC_Box_h), 0);
			gtk_widget_set_can_focus(Channel13_LE_DAC_Box_h, 0);
			gtk_entry_set_text(GTK_ENTRY(Channel14_LE_DAC_Box_h), "N/A");
			gtk_editable_set_editable(GTK_EDITABLE(Channel14_LE_DAC_Box_h), 0);
			gtk_widget_set_can_focus(Channel14_LE_DAC_Box_h, 0);
			gtk_entry_set_text(GTK_ENTRY(Channel15_LE_DAC_Box_h), "N/A");
			gtk_editable_set_editable(GTK_EDITABLE(Channel15_LE_DAC_Box_h), 0);
			gtk_widget_set_can_focus(Channel15_LE_DAC_Box_h, 0);
	}
	else
	{
			gtk_entry_set_text(GTK_ENTRY(Channel1_LE_DAC_Box_h), "");
			gtk_editable_set_editable(GTK_EDITABLE(Channel1_LE_DAC_Box_h), 1);
			gtk_widget_set_can_focus(Channel1_LE_DAC_Box_h, 1);
			gtk_entry_set_text(GTK_ENTRY(Channel2_LE_DAC_Box_h), "");
			gtk_editable_set_editable(GTK_EDITABLE(Channel2_LE_DAC_Box_h), 1);
			gtk_widget_set_can_focus(Channel2_LE_DAC_Box_h, 1);
			gtk_entry_set_text(GTK_ENTRY(Channel3_LE_DAC_Box_h), "");
			gtk_editable_set_editable(GTK_EDITABLE(Channel3_LE_DAC_Box_h), 1);
			gtk_widget_set_can_focus(Channel3_LE_DAC_Box_h, 1);
			gtk_entry_set_text(GTK_ENTRY(Channel4_LE_DAC_Box_h), "");
			gtk_editable_set_editable(GTK_EDITABLE(Channel4_LE_DAC_Box_h), 1);
			gtk_widget_set_can_focus(Channel4_LE_DAC_Box_h, 1);
			gtk_entry_set_text(GTK_ENTRY(Channel5_LE_DAC_Box_h), "");
			gtk_editable_set_editable(GTK_EDITABLE(Channel5_LE_DAC_Box_h), 1);
			gtk_widget_set_can_focus(Channel5_LE_DAC_Box_h, 1);
			gtk_entry_set_text(GTK_ENTRY(Channel6_LE_DAC_Box_h), "");
			gtk_editable_set_editable(GTK_EDITABLE(Channel6_LE_DAC_Box_h), 1);
			gtk_widget_set_can_focus(Channel6_LE_DAC_Box_h, 1);
			gtk_entry_set_text(GTK_ENTRY(Channel7_LE_DAC_Box_h), "");
			gtk_editable_set_editable(GTK_EDITABLE(Channel7_LE_DAC_Box_h), 1);
			gtk_widget_set_can_focus(Channel7_LE_DAC_Box_h, 1);
			gtk_entry_set_text(GTK_ENTRY(Channel8_LE_DAC_Box_h), "");
			gtk_editable_set_editable(GTK_EDITABLE(Channel8_LE_DAC_Box_h), 1);
			gtk_widget_set_can_focus(Channel8_LE_DAC_Box_h, 1);
			gtk_entry_set_text(GTK_ENTRY(Channel9_LE_DAC_Box_h), "");
			gtk_editable_set_editable(GTK_EDITABLE(Channel9_LE_DAC_Box_h), 1);
			gtk_widget_set_can_focus(Channel9_LE_DAC_Box_h, 1);
			gtk_entry_set_text(GTK_ENTRY(Channel10_LE_DAC_Box_h), "");
			gtk_editable_set_editable(GTK_EDITABLE(Channel10_LE_DAC_Box_h), 1);
			gtk_widget_set_can_focus(Channel10_LE_DAC_Box_h, 1);
			gtk_entry_set_text(GTK_ENTRY(Channel11_LE_DAC_Box_h), "");
			gtk_editable_set_editable(GTK_EDITABLE(Channel11_LE_DAC_Box_h), 1);
			gtk_widget_set_can_focus(Channel11_LE_DAC_Box_h, 1);
			gtk_entry_set_text(GTK_ENTRY(Channel12_LE_DAC_Box_h), "");
			gtk_editable_set_editable(GTK_EDITABLE(Channel12_LE_DAC_Box_h), 1);
			gtk_widget_set_can_focus(Channel12_LE_DAC_Box_h, 1);
			gtk_entry_set_text(GTK_ENTRY(Channel13_LE_DAC_Box_h), "");
			gtk_editable_set_editable(GTK_EDITABLE(Channel13_LE_DAC_Box_h), 1);
			gtk_widget_set_can_focus(Channel13_LE_DAC_Box_h, 1);
			gtk_entry_set_text(GTK_ENTRY(Channel14_LE_DAC_Box_h), "");
			gtk_editable_set_editable(GTK_EDITABLE(Channel14_LE_DAC_Box_h), 1);
			gtk_widget_set_can_focus(Channel14_LE_DAC_Box_h, 1);
			gtk_entry_set_text(GTK_ENTRY(Channel15_LE_DAC_Box_h), "");
			gtk_editable_set_editable(GTK_EDITABLE(Channel15_LE_DAC_Box_h), 1);
			gtk_widget_set_can_focus(Channel15_LE_DAC_Box_h, 1);
	}

	printf("GMode toggled: %s\n", (gmode) ? "ON":"OFF");
}

void on_Neg_Pol_CB_toggled()
{
	GtkToggleButton* neg_pol_cb = GTK_TOGGLE_BUTTON(Neg_Pol_CB_h);

	neg_pol = (gtk_toggle_button_get_active(neg_pol_cb)) ? 1:0;
	printf("Neg pol toggled: %s\n", (neg_pol) ? "ON":"OFF");
}

void on_Internal_AGND_CB_toggled()
{
	GtkToggleButton* agnd_cb = GTK_TOGGLE_BUTTON(Internal_AGND_CB_h);

	int_agnd_en = (gtk_toggle_button_get_active(agnd_cb)) ? 1:0;
	printf("Internal AGND toggled: %s\n", (int_agnd_en) ? "ON":"OFF");
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

	gtk_combo_box_set_active(GTK_COMBO_BOX(delaybox), 0);

}

void on_Nowlin_Delay_Menu_changed()
{
	GtkComboBoxText* delaybox = GTK_COMBO_BOX_TEXT(Nowlin_Delay_Menu_h);
	
	gchar* delay = gtk_combo_box_text_get_active_text(delaybox);
	g_printf("Nowlin delay menu changed: %s ns\n", delay);
}

void on_Test_Point_Menu_changed()
{
	GtkComboBoxText* tp_box = GTK_COMBO_BOX_TEXT(Test_Point_Menu_h);
	gchar* tp = gtk_combo_box_text_get_active_text(tp_box);

	gint index = gtk_combo_box_get_active(GTK_COMBO_BOX(tp_box));
	test_point_sel = (char)index;

	g_printf("Test point menu changed: %s\n", tp);
}

void on_Lockout_Mode_Menu_changed()
{
	GtkComboBoxText* modebox = GTK_COMBO_BOX_TEXT(Lockout_Mode_Menu_h);
	GtkEntry* lockout_dac = GTK_ENTRY(Lockout_DAC_Box_h);
	
	gchar* mode = gtk_combo_box_text_get_active_text(modebox);
	const char* str;

	if(g_strcmp0(mode, "Disabled") == 0)
	{
		gtk_entry_set_text(lockout_dac, "N/A");
		gtk_editable_set_editable(GTK_EDITABLE(lockout_dac), 0);
		lockout_mode = LOCKOUT_DISABLED;
		gtk_widget_set_can_focus(Lockout_DAC_Box_h, 0);
		str = "DISABLED";
	}
	else if(g_strcmp0(mode, "Short") == 0)
	{
		gtk_entry_set_text(lockout_dac, "");
		gtk_editable_set_editable(GTK_EDITABLE(lockout_dac), 1);
		gtk_widget_set_can_focus(Lockout_DAC_Box_h, 1);
		lockout_mode = LOCKOUT_SHORT;
		str = "SHORT";
	}
	else
	{
		gtk_entry_set_text(lockout_dac, "");
		gtk_editable_set_editable(GTK_EDITABLE(lockout_dac), 1);
		gtk_widget_set_can_focus(Lockout_DAC_Box_h, 1);
		lockout_mode = LOCKOUT_LONG;
		str = "LONG";
	}

	printf("Lockout mode menu changed: %s\n", str);
}

void on_AGND_Trim_Menu_changed()
{
	GtkComboBoxText* agnd_box = GTK_COMBO_BOX_TEXT(AGND_Trim_Menu_h);
	gchar* val = gtk_combo_box_text_get_active_text(agnd_box);

	gint index = gtk_combo_box_get_active(GTK_COMBO_BOX(agnd_box));
	agnd_trim = (char)index;

	g_printf("AGND trim menu changed: %s\n", val);
}

void channel_enable_event(int channel)
{
	printf("Channel%i enable toggled\n", channel);

	ch_en[channel] ^= 1;	

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

void on_Configure_Button_clicked()
{
	printf("Configure button clicked\n");
}

void on_Save_Config_Button_clicked()
{
	GtkEntry* save_file = GTK_ENTRY(Save_File_Box_h);
	const gchar* filename = gtk_entry_get_text(save_file);

	FILE* fd = fopen((const char*)filename, "w");

	if(!fd)
	{
		perror("Failed to open file\n");
		exit(EXIT_FAILURE);
	}

	fwrite(&gen, sizeof(gen), 1, fd);
	fwrite(&neg_pol, sizeof(neg_pol), 1, fd);
	fwrite(&int_agnd_en, sizeof(int_agnd_en), 1, fd);
	fwrite(&agnd_trim, sizeof(agnd_trim), 1, fd);
	fwrite(&nowlin_mode, sizeof(nowlin_mode), 1, fd);
	fwrite(&nowlin_delay, sizeof(nowlin_delay), 1, fd);
	fwrite(&lockout_mode, sizeof(lockout_mode), 1, fd);
	fwrite(&lockout_dac, sizeof(lockout_dac), 1, fd);
	fwrite(&test_point_sel, sizeof(test_point_sel), 1, fd);
	fwrite(&gmode, sizeof(gmode), 1, fd);
	
	if(gmode)
	{
		fwrite(leading_edge_dac, sizeof(leading_edge_dac[0]), 1, fd);
	}
	else
	{
		fwrite(leading_edge_dac, CHANNELS*sizeof(leading_edge_dac[0]), CHANNELS, fd);
	}

	fwrite(ch_en, CHANNELS*sizeof(ch_en[0]), CHANNELS, fd);

	fclose(fd);

	g_printf("File saved to: %s\n", filename);
}

void on_Load_File_Button_selection_changed()
{
	GtkFileChooser* file = GTK_FILE_CHOOSER(Load_File_Box_h);
	gchar* filename = gtk_file_chooser_get_filename(file);
	
	FILE* fd = fopen((const char*)filename, "r");

	if(!fd)
	{
		perror("Failed to open file\n");
		exit(EXIT_FAILURE);
	}

	fread(&gen, sizeof(gen), 1, fd);
	g_signal_handlers_block_by_func(GEN_CB_h, G_CALLBACK(on_GEN_CB_toggled), NULL);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(GEN_CB_h), gen);	
	g_signal_handlers_unblock_by_func(GEN_CB_h, G_CALLBACK(on_GEN_CB_toggled), NULL);

	fread(&neg_pol, sizeof(neg_pol), 1, fd);
	GtkToggleButton* neg_pol_cb = GTK_TOGGLE_BUTTON(Neg_Pol_CB_h);
	gtk_toggle_button_set_active(neg_pol_cb, neg_pol);

	fread(&int_agnd_en, sizeof(int_agnd_en), 1, fd);
	fread(&agnd_trim, sizeof(agnd_trim), 1, fd);
	fread(&nowlin_mode, sizeof(nowlin_mode), 1, fd);
	fread(&nowlin_delay, sizeof(nowlin_delay), 1, fd);
	fread(&lockout_mode, sizeof(lockout_mode), 1, fd);
	fread(&lockout_dac, sizeof(lockout_dac), 1, fd);
	fread(&test_point_sel, sizeof(test_point_sel), 1, fd);
	fread(&gmode, sizeof(gmode), 1, fd);
	
	if(gmode)
	{
		fread(leading_edge_dac, sizeof(leading_edge_dac[0]), 1, fd);
	}
	else
	{
		fread(leading_edge_dac, CHANNELS*sizeof(leading_edge_dac[0]), CHANNELS, fd);
	}

	fread(ch_en, CHANNELS*sizeof(ch_en[0]), CHANNELS, fd);

	fclose(fd);
	
	g_printf("Loaded configuration from file: %s\n", filename);
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

	Save_File_Box_h = GTK_WIDGET(gtk_builder_get_object(builder, "Save_File_Name_Box"));
	Load_File_Box_h = GTK_WIDGET(gtk_builder_get_object(builder, "Load_File_Button"));
	Save_File_Button_h = GTK_WIDGET(gtk_builder_get_object(builder, "Save_Config_Button"));

	/* Set default values for configuration */
	gen = 1; //enable chip
	gmode = 0; //global mode disabled -- each channel DAC configured individually
	neg_pol = 0; //positive polarity
	int_agnd_en = 1; //enable internal generation of AGND
	agnd_trim = AGND_1_63; //set AGND for 1.63V (nominal value)
	nowlin_mode = NOWLIN_SHORT; //nowlin short mode
	nowlin_delay = 1; //set Nowlin delay for 2 ns (switch in 1 cap at short mode)
	lockout_mode = LOCKOUT_DISABLED; //disable lockout
	test_point_sel = TP_AVSS; //set test point to AVSS (no test point connected)
	lockout_dac = 0; //set lockout DAC to 0 (doesnt matter since lockout disabled)

	for(int i = 0; i < CHANNELS; i++)
	{
		ch_en[i] = 1; //by default enable all channels
		leading_edge_dac[i] = 0; //by default all DACs loaded with 0
	}


	GtkEntry* lockout_dac = GTK_ENTRY(Lockout_DAC_Box_h);	
	gtk_entry_set_text(lockout_dac, "N/A");
	gtk_editable_set_editable(GTK_EDITABLE(lockout_dac), 0);
	gtk_widget_set_can_focus(Lockout_DAC_Box_h, 0);

    gtk_builder_connect_signals(builder, NULL);
    printf("connect returned\n");

    g_object_unref(builder);
    printf("unref returned\n");

    gtk_widget_show(window);
    printf("show returned\n");
    gtk_main();

    return 0;
}
