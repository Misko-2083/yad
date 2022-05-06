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
  gchar *path;

  path =  g_file_get_path (data);

  if (path == NULL)
     path = g_file_get_uri (data);

  if (options.common_data.quoted_output)
    {
      gchar *buf = g_shell_quote (g_filename_to_utf8 (path, -1, NULL, NULL, NULL));
      g_printf ("%s", buf);
      g_free (buf);
    }
  else
     g_printf ("%s", g_filename_to_utf8 (path, -1, NULL, NULL, NULL));

  g_printf ("\n");
  fflush (stdout);

  g_free(path);
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
