#ifndef DRIVER_ISO9960_FS_H
#define DRIVER_ISO9960_FS_H

/* ISO9960 (CDROM) File system
http://users.telenet.be/it3.consultants.bvba/handouts/ISO9960.html
*/

struct _iso_primary_descriptor{
  unsigned char type;
  unsigned char id;
  unsigned char version;
  unsigned char unused1;
  unsigned char system_id;
  unsigned char volume_id;
  unsigned char unused2;
  unsigned char volume_space_size;
  unsigned char unused3;
  unsigned char volume_set_size;
  unsigned char volume_sequence_number;
  unsigned char logical_block_size;
  unsigned char path_table_size;
  unsigned char type_l_path_table;
  unsigned char opt_type_l_path_table;
  unsigned char type_m_path_table;
  unsigned char opt_type_m_path_table;
  unsigned char root_directory_record;
  unsigned char volume_set_id;
  unsigned char publisher_id;
  unsigned char preparer_id;
  unsigned char application_id;
  unsigned char copyright_file_id;
  unsigned char bibliographic_file_id;
  unsigned char creation_date;
  unsigned char modification_date;
  unsigned char expiration_date;
  unsigned char effective_date;
  unsigned char file_structure_version;
  unsigned char unused4;
  unsigned char application_data;
  unsigned char unused5;
};

typedef struct _iso_primary_descriptor iso_primary_descriptor_t;

struct _iso_directory_record{
  unsigned char length;
  unsigned char ext_attr_length;
  unsigned char extent;
  unsigned char size;
  unsigned char date;
  unsigned char flags;
  unsigned char file_unit_size;
  unsigned char interleave;
  unsigned char volume_sequence_number;
  unsigned char name_len;
  unsigned char name;
};

typedef struct _iso_directory_record iso_directory_record_t;


#endif;
