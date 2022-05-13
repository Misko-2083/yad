/*
 * This file is part of YAD.
 *
 * YAD is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * YAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with YAD. If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) 2022, Miloš Pavlovć <mpsrbija@gmail.com>
 */

#include "yad.h"

static GtkWidget *placessiderbar;

static void
places_sidebar_activated_cb (GtkPlacesSidebar * placessiderbar, gpointer data)
{
  GError *error = NULL;
  GFileEnumerator *enumerator = NULL;
  GFileQueryInfoFlags flags = G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS;
  const char* attributes = "standard::*, G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME";

  enumerator = g_file_enumerate_children (data, attributes,
                                         flags,
                                         NULL,
                                         &error);

  if (!g_file_enumerator_next_file (enumerator, NULL, NULL))  // If folder is empty
      g_print ("\n");

  if (error)
    g_printerr ("%s\n", error->message);

  while (TRUE)
  {
     GFileInfo *info;
     GFile *child = NULL;
     gchar *name;

     if (!g_file_enumerator_iterate (enumerator, &info, NULL, NULL, &error))
       goto out;
     if (!info)
       break;

     child = g_file_enumerator_get_child (enumerator, info);
     name = g_file_get_parse_name (child);

     g_printf ("%s\n", name);

     g_free(name);

     if (child)
       g_object_unref(child);
  }

  out:
    g_object_unref(enumerator);

  fflush (stdout);

  if (error) {
     g_printerr ("%s\n", error->message);
     g_error_free (error);
  }
}

GtkWidget *
places_sidebar_create_widget (GtkWidget * dlg)
{
  GtkWidget *w;

  w = placessiderbar = gtk_places_sidebar_new ();
  gtk_widget_set_name (w, "yad-places-widget");

  g_signal_connect (w, "open-location", G_CALLBACK (places_sidebar_activated_cb), dlg);

  return w;
}
