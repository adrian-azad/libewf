/*
 * Library for the Expert Witness Compression Format Support (EWF)
 * The file format both used by EnCase and FTK are based upon EWF
 *
 * Copyright (c) 2006-2008, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations. All rights reserved.
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of the creator, related organisations, nor the names of
 *   its contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER, COMPANY AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#if !defined( _LIBEWF_H )
#define _LIBEWF_H

#include <libewf/libewf_definitions.h>
#include <libewf/libewf_extern.h>
#include <libewf/libewf_handle.h>
#include <libewf/libewf_types.h>

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Returns the library version
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
LIBEWF_EXTERN const wchar_t *libewf_get_version(
                              void );
#else
LIBEWF_EXTERN const char *libewf_get_version(
                           void );
#endif

/* Returns the flags for reading
 */
LIBEWF_EXTERN uint8_t libewf_get_flags_read(
                       void );

/* Returns the flags for reading and writing
 */
LIBEWF_EXTERN uint8_t libewf_get_flags_read_write(
                       void );

/* Returns the flags for writing
 */
LIBEWF_EXTERN uint8_t libewf_get_flags_write(
                       void );

/* Detects if a file is an EWF file (check for the EWF file signature)
 * Returns 1 if true, 0 if not or -1 on error
 */
#if ( 0 || defined( HAVE_WIDE_CHARACTER_TYPE ) ) && defined( HAVE_WIDE_CHARACTER_SUPPORT_FUNCTIONS )
LIBEWF_EXTERN int libewf_check_file_signature(
                   const wchar_t *filename );
#else
LIBEWF_EXTERN int libewf_check_file_signature(
                   const char *filename );
#endif

/* Globs the segment files according to the EWF naming schema
 * if the format is known the filename should contain the base of the filename
 * otherwise the function will try to determine the format based on the extension
 * Returns the amount of filenames if successful or -1 on error
 */
#if ( 0 || defined( HAVE_WIDE_CHARACTER_TYPE ) ) && defined( HAVE_WIDE_CHARACTER_SUPPORT_FUNCTIONS )
LIBEWF_EXTERN int libewf_glob(
                   const wchar_t *filename,
                   size_t length,
                   uint8_t format,
                   wchar_t **filenames[] );
#else
LIBEWF_EXTERN int libewf_glob(
                   const char *filename,
                   size_t length,
                   uint8_t format,
                   char **filenames[] );
#endif

/* Signals the libewf handle to abort its current activity
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_signal_abort(
                   LIBEWF_HANDLE *handle );

/* Opens a set of EWF file(s)
 * For reading files should contain all filenames that make up an EWF image
 * For writing files should contain the base of the filename, extentions like .e01 will be automatically added
 * Returns a pointer to the new instance of handle, NULL on error
 */
#if ( 0 || defined( HAVE_WIDE_CHARACTER_TYPE ) ) && defined( HAVE_WIDE_CHARACTER_SUPPORT_FUNCTIONS )
LIBEWF_EXTERN LIBEWF_HANDLE *libewf_open(
                              wchar_t * const filenames[],
                              uint16_t amount_of_files,
                              uint8_t flags );
#else
LIBEWF_EXTERN LIBEWF_HANDLE *libewf_open(
                              char * const filenames[],
                              uint16_t amount_of_files,
                              uint8_t flags );
#endif

/* Seeks a certain offset of the media data within the EWF file(s)
 * It will set the related file offset to the specific chunk offset
 * Returns the offset if seek is successful or -1 on error
 */
LIBEWF_EXTERN off64_t libewf_seek_offset(
                       LIBEWF_HANDLE *handle,
                       off64_t offset );

/* Prepares a buffer with chunk data after reading it according to the handle settings
 * intended for raw read
 * The buffer size cannot be larger than the chunk size
 * Returns the resulting chunk size or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_raw_read_prepare_buffer(
                       LIBEWF_HANDLE *handle,
                       void *buffer,
                       size_t buffer_size,
                       void *uncompressed_buffer,
                       size_t *uncompressed_buffer_size,
                       int8_t is_compressed,
                       uint32_t chunk_crc,
                       int8_t read_crc );

/* Reads 'raw' data from the curent offset into a buffer
 * size contains the size of the buffer
 * The function sets the chunk crc, is compressed and read crc values
 * Returns the amount of bytes read or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_raw_read_buffer(
                       LIBEWF_HANDLE *handle,
                       void *buffer,
                       size_t size,
                       int8_t *is_compressed,
                       uint32_t *chunk_crc,
                       int8_t *read_crc );

/* Reads data from the curent offset into a buffer
 * Returns the amount of bytes read or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_read_buffer(
                       LIBEWF_HANDLE *handle,
                       void *buffer,
                       size_t size );

/* Reads media data from an offset into a buffer
 * Returns the amount of bytes read or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_read_random(
                       LIBEWF_HANDLE *handle,
                       void *buffer,
                       size_t size,
                       off64_t offset );

/* Prepares a buffer with chunk data before writing according to the handle settings
 * intended for raw write
 * The buffer size cannot be larger than the chunk size
 * The function sets the chunk crc, is compressed and write crc values
 * Returns the resulting chunk size or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_raw_write_prepare_buffer(
                       LIBEWF_HANDLE *handle,
                       void *buffer,
                       size_t buffer_size,
                       void *compressed_buffer,
                       size_t *compressed_buffer_size,
                       int8_t *is_compressed,
                       uint32_t *chunk_crc,
                       int8_t *write_crc );

/* Writes 'raw' data in EWF format from a buffer at the current offset
 * the necessary settings of the write values must have been made
 * size contains the size of the data within the buffer while
 * data size contains the size of the actual input data
 * Will initialize write if necessary
 * Returns the amount of input bytes written, 0 when no longer bytes can be written or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_raw_write_buffer(
                       LIBEWF_HANDLE *handle,
                       void *buffer,
                       size_t size,
                       size_t data_size,
                       int8_t is_compressed,
                       uint32_t chunk_crc,
                       int8_t write_crc );

/* Writes data in EWF format from a buffer at the current offset
 * the necessary settings of the write values must have been made
 * Will initialize write if necessary
 * Returns the amount of input bytes written, 0 when no longer bytes can be written or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_write_buffer(
                       LIBEWF_HANDLE *handle,
                       void *buffer,
                       size_t size );

/* Writes data in EWF format from a buffer at an specific offset,
 * the necessary settings of the write values must have been made
 * Will initialize write if necessary
 * Returns the amount of input bytes written, 0 when no longer bytes can be written or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_write_random(
                       LIBEWF_HANDLE *handle,
                       void *buffer,
                       size_t size,
                       off64_t offset );

/* Finalizes the write by correcting the EWF the meta data in the segment files
 * This function is required after writing from stream
 * Returns the amount of input bytes written or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_write_finalize(
                       LIBEWF_HANDLE *handle );

/* Closes the EWF handle and frees memory used within the handle
 * Returns 0 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_close(
                   LIBEWF_HANDLE *handle );

/* Retrieves the amount of sectors per chunk from the media information
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_sectors_per_chunk(
                   LIBEWF_HANDLE *handle,
                   uint32_t *sectors_per_chunk );

/* Retrieves the amount of bytes per sector from the media information
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_bytes_per_sector(
                   LIBEWF_HANDLE *handle,
                   uint32_t *bytes_per_sector );

/* Retrieves the amount of sectors from the media information
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_amount_of_sectors(
                   LIBEWF_HANDLE *handle,
                   uint32_t *amount_of_sectors );

/* Retrieves the chunk size from the media information
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_chunk_size(
                   LIBEWF_HANDLE *handle,
                   size32_t *chunk_size );

/* Retrieves the error granularity from the media information
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_error_granularity(
                   LIBEWF_HANDLE *handle,
                   uint32_t *error_granularity );

/* Retrieves the compression values
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_compression_values(
                   LIBEWF_HANDLE *handle,
                   int8_t *compression_level,
                   uint8_t *compress_empty_block );

/* Retrieves the size of the contained media data
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_media_size(
                   LIBEWF_HANDLE *handle,
                   size64_t *media_size );

/* Retrieves the media type value
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_media_type(
                   LIBEWF_HANDLE *handle,
                   int8_t *media_type );

/* Retrieves the media flags
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_media_flags(
                   LIBEWF_HANDLE *handle,
                   int8_t *media_flags );

/* Retrieves the volume type value
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_volume_type(
                   LIBEWF_HANDLE *handle,
                   int8_t *volume_type );

/* Retrieves the format type value
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_format(
                   LIBEWF_HANDLE *handle,
                   uint8_t *format );

/* Retrieves the GUID
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_guid(
                   LIBEWF_HANDLE *handle,
                   uint8_t *guid,
                   size_t size );

/* Retrieves the MD5 hash
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_get_md5_hash(
                   LIBEWF_HANDLE *handle,
                   uint8_t *md5_hash,
                   size_t size );

/* Retrieves the delta segment filename
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#if defined( HAVE_WIDE_CHARACTER_TYPE ) && defined( HAVE_WIDE_CHARACTER_SUPPORT_FUNCTIONS )
LIBEWF_EXTERN int libewf_get_delta_segment_filename(
                   LIBEWF_HANDLE *handle,
                   wchar_t *filename,
                   size_t length );
#else
LIBEWF_EXTERN int libewf_get_delta_segment_filename(
                   LIBEWF_HANDLE *handle,
                   char *filename,
                   size_t length );
#endif

/* Retrieves the amount of acquiry errors
 * Returns 1 if successful, 0 if no acquiry errors are present or -1 on error
 */
LIBEWF_EXTERN int libewf_get_amount_of_acquiry_errors(
                   LIBEWF_HANDLE *handle,
                   uint32_t *amount_of_errors );

/* Retrieves the information of an acquiry error
 * Returns 1 if successful, 0 if no acquiry error could be found or -1 on error
 */
LIBEWF_EXTERN int libewf_get_acquiry_error(
                   LIBEWF_HANDLE *handle,
                   uint32_t index,
                   off64_t *first_sector,
                   uint32_t *amount_of_sectors );

/* Retrieves the amount of CRC errors
 * Returns 1 if successful, 0 if no CRC errors are present or -1 on error
 */
LIBEWF_EXTERN int libewf_get_amount_of_crc_errors(
                   LIBEWF_HANDLE *handle,
                   uint32_t *amount_of_errors );

/* Retrieves the information of a CRC error
 * Returns 1 if successful, 0 if no CRC error could be found or -1 on error
 */
LIBEWF_EXTERN int libewf_get_crc_error(
                   LIBEWF_HANDLE *handle,
                   uint32_t index,
                   off64_t *first_sector,
                   uint32_t *amount_of_sectors );

/* Retrieves the amount of sessions
 * Returns 1 if successful, 0 if no sessions are present or -1 on error
 */
LIBEWF_EXTERN int libewf_get_amount_of_sessions(
                   LIBEWF_HANDLE *handle,
                   uint32_t *amount_of_sessions );

/* Retrieves the information of a session
 * Returns 1 if successful, 0 if no sessions could be found or -1 on error
 */
LIBEWF_EXTERN int libewf_get_session(
                   LIBEWF_HANDLE *handle,
                   uint32_t index,
                   off64_t *first_sector,
                   uint32_t *amount_of_sectors );

/* Retrieves the amount of chunks written
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_write_amount_of_chunks(
                   LIBEWF_HANDLE *handle,
                   uint32_t *amount_of_chunks );

/* Retrieves the amount of header values
 * Returns 1 if successful, 0 if no header values are present or -1 on error
 */
LIBEWF_EXTERN int libewf_get_amount_of_header_values(
                   LIBEWF_HANDLE *handle,
                   uint32_t *amount_of_values );

/* Retrieves the header value identifier specified by its index
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
LIBEWF_EXTERN int libewf_get_header_value_identifier(
                   LIBEWF_HANDLE *handle,
                   uint32_t index,
                   wchar_t *value,
                   size_t length );
#else
LIBEWF_EXTERN int libewf_get_header_value_identifier(
                   LIBEWF_HANDLE *handle,
                   uint32_t index,
                   char *value,
                   size_t length );
#endif

/* Retrieves the header value specified by the identifier
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
LIBEWF_EXTERN int libewf_get_header_value(
                   LIBEWF_HANDLE *handle,
                   wchar_t *identifier,
                   wchar_t *value,
                   size_t length );
#else
LIBEWF_EXTERN int libewf_get_header_value(
                   LIBEWF_HANDLE *handle,
                   char *identifier,
                   char *value,
                   size_t length );
#endif

/* Retrieves the header value case number
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_get_header_value_case_number( handle, value, length ) \
        libewf_get_header_value( handle, L"case_number", value, length )
#else
#define libewf_get_header_value_case_number( handle, value, length ) \
        libewf_get_header_value( handle, "case_number", value, length )
#endif

/* Retrieves the header value description
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_get_header_value_description( handle, value, length ) \
        libewf_get_header_value( handle, L"description", value, length )
#else
#define libewf_get_header_value_description( handle, value, length ) \
        libewf_get_header_value( handle, "description", value, length )
#endif

/* Retrieves the header value examiner name
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_get_header_value_examiner_name( handle, value, length ) \
        libewf_get_header_value( handle, L"examiner_name", value, length )
#else
#define libewf_get_header_value_examiner_name( handle, value, length ) \
        libewf_get_header_value( handle, "examiner_name", value, length )
#endif

/* Retrieves the header value evidence number
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_get_header_value_evidence_number( handle, value, length ) \
        libewf_get_header_value( handle, L"evidence_number", value, length )
#else
#define libewf_get_header_value_evidence_number( handle, value, length ) \
        libewf_get_header_value( handle, "evidence_number", value, length )
#endif

/* Retrieves the header value notes
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_get_header_value_notes( handle, value, length ) \
        libewf_get_header_value( handle, L"notes", value, length )
#else
#define libewf_get_header_value_notes( handle, value, length ) \
        libewf_get_header_value( handle, "notes", value, length )
#endif

/* Retrieves the header value acquiry date
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_get_header_value_acquiry_date( handle, value, length ) \
        libewf_get_header_value( handle, L"acquiry_date", value, length )
#else
#define libewf_get_header_value_acquiry_date( handle, value, length ) \
        libewf_get_header_value( handle, "acquiry_date", value, length )
#endif

/* Retrieves the header value system date
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_get_header_value_system_date( handle, value, length ) \
        libewf_get_header_value( handle, L"system_date", value, length )
#else
#define libewf_get_header_value_system_date( handle, value, length ) \
        libewf_get_header_value( handle, "system_date", value, length )
#endif

/* Retrieves the header value acquiry operating system
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_get_header_value_acquiry_operating_system( handle, value, length ) \
        libewf_get_header_value( handle, L"acquiry_operating_system", value, length )
#else
#define libewf_get_header_value_acquiry_operating_system( handle, value, length ) \
        libewf_get_header_value( handle, "acquiry_operating_system", value, length )
#endif

/* Retrieves the header value acquiry software version
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_get_header_value_acquiry_software_version( handle, value, length ) \
        libewf_get_header_value( handle, L"acquiry_software_version", value, length )
#else
#define libewf_get_header_value_acquiry_software_version( handle, value, length ) \
        libewf_get_header_value( handle, "acquiry_software_version", value, length )
#endif

/* Retrieves the header value password
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_get_header_value_password( handle, value, length ) \
        libewf_get_header_value( handle, L"password", value, length )
#else
#define libewf_get_header_value_password( handle, value, length ) \
        libewf_get_header_value( handle, "password", value, length )
#endif

/* Retrieves the header value compression type
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_get_header_value_compression_type( handle, value, length ) \
        libewf_get_header_value( handle, L"compression_type", value, length )
#else
#define libewf_get_header_value_compression_type( handle, value, length ) \
        libewf_get_header_value( handle, "compression_type", value, length )
#endif

/* Retrieves the header value model
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_get_header_value_model( handle, value, length ) \
        libewf_get_header_value( handle, L"model", value, length )
#else
#define libewf_get_header_value_model( handle, value, length ) \
        libewf_get_header_value( handle, "model", value, length )
#endif

/* Retrieves the header value serial number
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_get_header_value_serial_number( handle, value, length ) \
        libewf_get_header_value( handle, L"serial_number", value, length )
#else
#define libewf_get_header_value_serial_number( handle, value, length ) \
        libewf_get_header_value( handle, "serial_number", value, length )
#endif

/* Retrieves the amount of hash values
 * Returns 1 if successful, 0 if no hash values are present or -1 on error
 */
LIBEWF_EXTERN int libewf_get_amount_of_hash_values(
                   LIBEWF_HANDLE *handle,
                   uint32_t *amount_of_values );

/* Retrieves the hash value identifier specified by its index
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
LIBEWF_EXTERN int libewf_get_hash_value_identifier(
                   LIBEWF_HANDLE *handle,
                   uint32_t index,
                   wchar_t *value,
                   size_t length );
#else
LIBEWF_EXTERN int libewf_get_hash_value_identifier(
                   LIBEWF_HANDLE *handle,
                   uint32_t index,
                   char *value,
                   size_t length );
#endif

/* Retrieves the hash value specified by the identifier
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
LIBEWF_EXTERN int libewf_get_hash_value(
                   LIBEWF_HANDLE *handle,
                   wchar_t *identifier,
                   wchar_t *value,
                   size_t length );
#else
LIBEWF_EXTERN int libewf_get_hash_value(
                   LIBEWF_HANDLE *handle,
                   char *identifier,
                   char *value,
                   size_t length );
#endif

/* Retrieves the hash value MD5
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_get_hash_value_md5( handle, value, length ) \
        libewf_get_hash_value( handle, L"MD5", value, length )
#else
#define libewf_get_hash_value_md5( handle, value, length ) \
        libewf_get_hash_value( handle, "MD5", value, length )
#endif

/* Retrieves the hash value SHA1
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_get_hash_value_sha1( handle, value, length ) \
        libewf_get_hash_value( handle, L"SHA1", value, length )
#else
#define libewf_get_hash_value_sha1( handle, value, length ) \
        libewf_get_hash_value( handle, "SHA1", value, length )
#endif

/* Sets the amount of sectors per chunk in the media information
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_sectors_per_chunk(
                   LIBEWF_HANDLE *handle,
                   uint32_t sectors_per_chunk );

/* Sets the amount of bytes per sector in the media information
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_bytes_per_sector(
                   LIBEWF_HANDLE *handle,
                   uint32_t bytes_per_sector );

/* Sets the error granularity
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_error_granularity(
                   LIBEWF_HANDLE *handle,
                   uint32_t error_granularity );

/* Sets the compression values
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_compression_values(
                   LIBEWF_HANDLE *handle,
                   int8_t compression_level,
                   uint8_t compress_empty_block );

/* Sets the media size
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_media_size(
                   LIBEWF_HANDLE *handle,
                   size64_t media_size );

/* Sets the segment file size
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_segment_file_size(
                   LIBEWF_HANDLE *handle,
                   size64_t segment_file_size );

/* Sets the delta segment file size
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_delta_segment_file_size(
                   LIBEWF_HANDLE *handle,
                   size64_t delta_segment_file_size );

/* Sets the media type
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_media_type(
                   LIBEWF_HANDLE *handle,
                   uint8_t media_type );

/* Sets the volume type
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_volume_type(
                   LIBEWF_HANDLE *handle,
                   uint8_t volume_type );

/* Sets the output format
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_format(
                   LIBEWF_HANDLE *handle,
                   uint8_t format );

/* Sets the GUID
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_guid(
                   LIBEWF_HANDLE *handle,
                   uint8_t *guid,
                   size_t size );

/* Sets the MD5 hash
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_set_md5_hash(
                   LIBEWF_HANDLE *handle,
                   uint8_t *md5_hash,
                   size_t size );

/* Sets the delta segment file
 * Returns 1 if successful or -1 on error
 */
#if defined( HAVE_WIDE_CHARACTER_TYPE ) && defined( HAVE_WIDE_CHARACTER_SUPPORT_FUNCTIONS )
LIBEWF_EXTERN int libewf_set_delta_segment_filename(
                   LIBEWF_HANDLE *handle,
                   wchar_t *filename,
                   size_t length );
#else
LIBEWF_EXTERN int libewf_set_delta_segment_filename(
                   LIBEWF_HANDLE *handle,
                   char *filename,
                   size_t length );
#endif

/* Sets the read wipe chunk on error
 * The chunk is not wiped if read raw is used
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_read_wipe_chunk_on_error(
                   LIBEWF_HANDLE *handle,
                   uint8_t wipe_on_error );

/* Sets the header value specified by the identifier
 * Returns 1 if successful or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
LIBEWF_EXTERN int libewf_set_header_value(
                   LIBEWF_HANDLE *handle,
                   wchar_t *identifier,
                   wchar_t *value,
                   size_t length );
#else
LIBEWF_EXTERN int libewf_set_header_value(
                   LIBEWF_HANDLE *handle,
                   char *identifier,
                   char *value,
                   size_t length );
#endif

/* Sets the header value case number
 * Returns 1 if successful or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_set_header_value_case_number( handle, value, length ) \
        libewf_set_header_value( handle, L"case_number", value, length )
#else
#define libewf_set_header_value_case_number( handle, value, length ) \
        libewf_set_header_value( handle, "case_number", value, length )
#endif

/* Sets the header value description
 * Returns 1 if successful or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_set_header_value_description( handle, value, length ) \
        libewf_set_header_value( handle, L"description", value, length )
#else
#define libewf_set_header_value_description( handle, value, length ) \
        libewf_set_header_value( handle, "description", value, length )
#endif

/* Sets the header value examiner name
 * Returns 1 if successful or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_set_header_value_examiner_name( handle, value, length ) \
        libewf_set_header_value( handle, L"examiner_name", value, length )
#else
#define libewf_set_header_value_examiner_name( handle, value, length ) \
        libewf_set_header_value( handle, "examiner_name", value, length )
#endif

/* Sets the header value evidence number
 * Returns 1 if successful or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_set_header_value_evidence_number( handle, value, length ) \
        libewf_set_header_value( handle, L"evidence_number", value, length )
#else
#define libewf_set_header_value_evidence_number( handle, value, length ) \
        libewf_set_header_value( handle, "evidence_number", value, length )
#endif

/* Sets the header value notes
 * Returns 1 if successful or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_set_header_value_notes( handle, value, length ) \
        libewf_set_header_value( handle, L"notes", value, length )
#else
#define libewf_set_header_value_notes( handle, value, length ) \
        libewf_set_header_value( handle, "notes", value, length )
#endif

/* Sets the header value acquiry date
 * Returns 1 if successful or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_set_header_value_acquiry_date( handle, value, length ) \
        libewf_set_header_value( handle, L"acquiry_date", value, length )
#else
#define libewf_set_header_value_acquiry_date( handle, value, length ) \
        libewf_set_header_value( handle, "acquiry_date", value, length )
#endif

/* Sets the header value system date
 * Returns 1 if successful or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_set_header_value_system_date( handle, value, length ) \
        libewf_set_header_value( handle, L"system_date", value, length )
#else
#define libewf_set_header_value_system_date( handle, value, length ) \
        libewf_set_header_value( handle, "system_date", value, length )
#endif

/* Sets the header value acquiry operating system
 * Returns 1 if successful or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_set_header_value_acquiry_operating_system( handle, value, length ) \
        libewf_set_header_value( handle, L"acquiry_operating_system", value, length )
#else
#define libewf_set_header_value_acquiry_operating_system( handle, value, length ) \
        libewf_set_header_value( handle, "acquiry_operating_system", value, length )
#endif

/* Sets the header value acquiry software version
 * Returns 1 if successful or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_set_header_value_acquiry_software_version( handle, value, length ) \
        libewf_set_header_value( handle, L"acquiry_software_version", value, length )
#else
#define libewf_set_header_value_acquiry_software_version( handle, value, length ) \
        libewf_set_header_value( handle, "acquiry_software_version", value, length )
#endif

/* Sets the header value password
 * Returns 1 if successful or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_set_header_value_password( handle, value, length ) \
        libewf_set_header_value( handle, L"password", value, length )
#else
#define libewf_set_header_value_password( handle, value, length ) \
        libewf_set_header_value( handle, "password", value, length )
#endif

/* Sets the header value compression type
 * Returns 1 if successful or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_set_header_value_compression_type( handle, value, length ) \
        libewf_set_header_value( handle, L"compression_type", value, length )
#else
#define libewf_set_header_value_compression_type( handle, value, length ) \
        libewf_set_header_value( handle, "compression_type", value, length )
#endif

/* Sets the header value model
 * Returns 1 if successful or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_set_header_value_model( handle, value, length ) \
        libewf_set_header_value( handle, L"model", value, length )
#else
#define libewf_set_header_value_model( handle, value, length ) \
        libewf_set_header_value( handle, "model", value, length )
#endif

/* Sets the header value serial number
 * Returns 1 if successful or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_set_header_value_serial_number( handle, value, length ) \
        libewf_set_header_value( handle, L"serial_number", value, length )
#else
#define libewf_set_header_value_serial_number( handle, value, length ) \
        libewf_set_header_value( handle, "serial_number", value, length )
#endif

/* Sets the hash value specified by the identifier
 * Returns 1 if successful or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
LIBEWF_EXTERN int libewf_set_hash_value(
                   LIBEWF_HANDLE *handle,
                   wchar_t *identifier,
                   wchar_t *value,
                   size_t length );
#else
LIBEWF_EXTERN int libewf_set_hash_value(
                   LIBEWF_HANDLE *handle,
                   char *identifier,
                   char *value,
                   size_t length );
#endif

/* Sets the hash value MD5
 * Returns 1 if successful or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_set_hash_value_md5( handle, value, length ) \
        libewf_set_hash_value( handle, L"MD5", value, length )
#else
#define libewf_set_hash_value_md5( handle, value, length ) \
        libewf_set_hash_value( handle, "MD5", value, length )
#endif

/* Sets the hash value SHA1
 * Returns 1 if successful or -1 on error
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define libewf_set_hash_value_sha1( handle, value, length ) \
        libewf_set_hash_value( handle, L"SHA1", value, length )
#else
#define libewf_set_hash_value_sha1( handle, value, length ) \
        libewf_set_hash_value( handle, "SHA1", value, length )
#endif

/* Parses the header values from the xheader, header2 or header section
 * Will parse the first available header in order mentioned above
 * Returns 1 if successful, 0 if already parsed or -1 on error
 */
LIBEWF_EXTERN int libewf_parse_header_values(
                   LIBEWF_HANDLE *handle,
                   uint8_t date_format );

/* Parses the hash values from the xhash section
 * Returns 1 if successful, 0 if already parsed or -1 on error
 */
LIBEWF_EXTERN int libewf_parse_hash_values(
                   LIBEWF_HANDLE *handle );

/* Add an acquiry error
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_add_acquiry_error(
                   LIBEWF_HANDLE *handle,
                   off64_t first_sector,
                   uint32_t amount_of_sectors );

/* Add a CRC error
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_add_crc_error(
                   LIBEWF_HANDLE *handle,
                   off64_t first_sector,
                   uint32_t amount_of_sectors );

/* Add a session
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_add_session(
                   LIBEWF_HANDLE *handle,
                   off64_t first_sector,
                   uint32_t amount_of_sectors );

/* Copies the header values from the source to the destination handle
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_copy_header_values(
                   LIBEWF_HANDLE *destination_handle,
                   LIBEWF_HANDLE *source_handle );

/* Copies the media values from the source to the destination handle
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_copy_media_values(
                   LIBEWF_HANDLE *destination_handle,
                   LIBEWF_HANDLE *source_handle );

/* Set the notify values
 */
LIBEWF_EXTERN void libewf_set_notify_values(
                   FILE *stream,
                   uint8_t verbose );

#ifdef __cplusplus
}
#endif

#endif

