/* $Id$*/

#include <gtk/gtk.h>
#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/callback.h>
#include <caml/fail.h>

#include "wrappers.h"
#include "ml_glib.h"
#include "ml_gobject.h"
#include "ml_gtk.h"
#include "gtk_tags.h"

CAMLprim value ml_gtkaction_init(value unit)
{
  GType t =
#ifdef HASGTK24
    gtk_action_get_type () +
    gtk_toggle_action_get_type () +
    gtk_radio_action_get_type () +
    gtk_toggle_action_get_type () +
    gtk_action_group_get_type () +
    gtk_ui_manager_get_type () ;
#else
    0;
#endif
  return Val_GType(t);
}

#ifdef HAS_GTK24

#define gobject_list_of_GSList(l) Val_GSList(l, (value_in) Val_GObject)
#define gobject_list_of_GList(l)  Val_GList (l, (value_in) Val_GObject)
#define gobject_list_of_GList_free(l)  Val_GList_free (l, (value_in) Val_GObject)


/* gtkaction.h */
#define GtkAction_val(val) check_cast(GTK_ACTION, val)
ML_1 (gtk_action_activate, GtkAction_val, Unit)
ML_2 (gtk_action_connect_proxy, GtkAction_val, GtkWidget_val, Unit)
ML_2 (gtk_action_disconnect_proxy, GtkAction_val, GtkWidget_val, Unit)
ML_1 (gtk_action_get_proxies, GtkAction_val, gobject_list_of_GSList)
ML_1 (gtk_action_connect_accelerator, GtkAction_val, Unit)
ML_1 (gtk_action_disconnect_accelerator, GtkAction_val, Unit)
ML_2 (gtk_action_set_accel_path, GtkAction_val, String_val, Unit)

/* gtktoggleaction.h */
#define GtkToggleAction_val(val) check_cast(GTK_TOGGLE_ACTION, val)
ML_1 (gtk_toggle_action_toggled, GtkToggleAction_val, Unit)
ML_2 (gtk_toggle_action_set_active, GtkToggleAction_val, Bool_val, Unit)
ML_1 (gtk_toggle_action_get_active, GtkToggleAction_val, Val_bool)


/* gtkradioaction.h */
#define GtkRadioAction_val(val) check_cast(GTK_RADIO_ACTION, val)
CAMLprim value ml_gtk_radio_action_set_group(value ac, value grp)
{
  GtkRadioAction *grp_ac = Option_val(grp, GtkRadioAction_val, NULL);
  GSList *slist = grp_ac ? gtk_radio_action_get_group(grp_ac) : NULL;
  gtk_radio_action_set_group(GtkRadioAction_val(ac), slist);
  return Val_unit;
}
ML_1 (gtk_radio_action_get_current_value, GtkRadioAction_val, Val_int)


/* gtkactiongroup.h */
#define GtkActionGroup_val(val) check_cast(GTK_ACTION_GROUP, val)
ML_2 (gtk_action_group_get_action, GtkActionGroup_val, String_val, Val_GAnyObject)
ML_1 (gtk_action_group_list_actions, GtkActionGroup_val, gobject_list_of_GList_free)
ML_2 (gtk_action_group_add_action, GtkActionGroup_val, GtkAction_val, Unit)
ML_2 (gtk_action_group_remove_action, GtkActionGroup_val, GtkAction_val, Unit)


/* gtkuimanager.h */
#define GtkUIManager_val(val) check_cast(GTK_UI_MANAGER, val)
ML_3 (gtk_ui_manager_insert_action_group, GtkUIManager_val, GtkActionGroup_val, Int_val, Unit)
ML_2 (gtk_ui_manager_remove_action_group, GtkUIManager_val, GtkActionGroup_val, Unit)
ML_1 (gtk_ui_manager_get_action_groups, GtkUIManager_val, gobject_list_of_GList)
ML_1 (gtk_ui_manager_get_accel_group, GtkUIManager_val, Val_GtkAccelGroup)
ML_2 (gtk_ui_manager_get_widget, GtkUIManager_val, String_val, Val_GtkWidget)
ML_2 (gtk_ui_manager_get_action, GtkUIManager_val, String_val, Val_GAnyObject)
CAMLprim value ml_gtk_ui_manager_add_ui_from_string(value uim, value s)
{
  return Val_int(gtk_ui_manager_add_ui_from_string(GtkUIManager_val(uim),
						   String_val(s), -1, NULL));
}
CAMLprim value ml_gtk_ui_manager_add_ui_from_file(value uim, value s)
{
  return Val_int(gtk_ui_manager_add_ui_from_file(GtkUIManager_val(uim),
						 String_val(s), NULL));
}
ML_2 (gtk_ui_manager_remove_ui, GtkUIManager_val, Int_val, Unit)
ML_1 (gtk_ui_manager_ensure_update, GtkUIManager_val, Unit)
/* ML_1 (gtk_ui_manager_new_merge_id, GtkUIManager_val, Val_int) */

#else /* HASGTK24 */

Unsupported_24(gtk_action_activate)
Unsupported_24(gtk_action_connect_proxy)
Unsupported_24(gtk_action_disconnect_proxy)
Unsupported_24(gtk_action_get_proxies)
Unsupported_24(gtk_action_connect_accelerator)
Unsupported_24(gtk_action_disconnect_accelerator)
Unsupported_24(gtk_action_set_accel_path)
Unsupported_24(gtk_toggle_action_toggled)
Unsupported_24(gtk_toggle_action_set_active)
Unsupported_24(gtk_toggle_action_get_active)
Unsupported_24(gtk_radio_action_set_group)
Unsupported_24(gtk_radio_action_get_current_value)
Unsupported_24(gtk_action_group_get_action)
Unsupported_24(gtk_action_group_list_actions)
Unsupported_24(gtk_action_group_add_action)
Unsupported_24(gtk_action_group_remove_action)
Unsupported_24(gtk_ui_manager_insert_action_group)
Unsupported_24(gtk_ui_manager_remove_action_group)
Unsupported_24(gtk_ui_manager_get_action_groups)
Unsupported_24(gtk_ui_manager_get_accel_group)
Unsupported_24(gtk_ui_manager_get_widget)
Unsupported_24(gtk_ui_manager_get_action)
Unsupported_24(gtk_ui_manager_add_ui_from_string)
Unsupported_24(gtk_ui_manager_add_ui_from_file)
Unsupported_24(gtk_ui_manager_remove_ui)
Unsupported_24(gtk_ui_manager_ensure_update)

#endif /* HASGTK24 */