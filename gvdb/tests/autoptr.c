/* SPDX-FileCopyrightText: 2025 GNOME Foundation, Inc.
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#include <glib.h>
#include <unistd.h>

#include "gvdb/gvdb-builder.h"
#include "gvdb/gvdb-reader.h"

static void
remove_file (const gchar *filename)
{
  g_assert_no_errno (unlink (filename));
}

static void
test_autoptr_table (void)
{
  g_autofree char *filename = g_build_filename (g_get_tmp_dir (), "autoptr-table.gvdb", NULL);
  g_autoptr(GvdbTable) table = NULL;
  g_autoptr(GHashTable) build_table = NULL;
  GError *local_error = NULL;

  g_assert_null (table);

  /* Build a table to read back */
  build_table = gvdb_hash_table_new (NULL, "level1");
  gvdb_hash_table_insert_string (build_table, "key1", "here just a flat string");
  gvdb_table_write_contents (build_table, filename, FALSE, &local_error);
  g_assert_no_error (local_error);

  table = gvdb_table_new (filename, TRUE, &local_error);
  g_assert_no_error (local_error);
  g_assert_nonnull (table);

  /* Clean up. The autoptr code should be executed after this */
  remove_file (filename);
}

int
main (int    argc,
      char **argv)
{
  g_test_init (&argc, &argv, G_TEST_OPTION_ISOLATE_DIRS, NULL);

  g_test_add_func ("/autoptr/table", test_autoptr_table);

  return g_test_run ();
}
