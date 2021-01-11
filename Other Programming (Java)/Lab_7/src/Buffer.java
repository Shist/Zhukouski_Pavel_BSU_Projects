import java.io.*;
import java.util.zip.*;

public class Buffer {
    static byte[] toByteArray( Serializable obj ) throws IOException {
        ByteArrayOutputStream bufOut = new ByteArrayOutputStream();
        try ( ZipOutputStream zos = new ZipOutputStream( bufOut )) {
            zos.putNextEntry( new ZipEntry("r"));
            try ( ObjectOutputStream oos = new ObjectOutputStream( zos )) {
                oos.writeObject( obj );
                oos.flush();
                zos.closeEntry();
                zos.flush();
                return bufOut.toByteArray();
            }
        }
    }
	
    static Object fromByteArray( byte[] arr ) 
            throws IOException, ClassNotFoundException {
        ByteArrayInputStream  bufIn = new ByteArrayInputStream( arr );
        try( ZipInputStream zis = new ZipInputStream( bufIn )) {
            /*ZipEntry zen = */
            zis.getNextEntry();
            try ( ObjectInputStream ois = new ObjectInputStream( zis )) {
                return ois.readObject();
            }
        }
    }
	
    public static long writeObject( RandomAccessFile file, Serializable obj ) 
            throws IOException {
        long result = file.length();
        file.seek( result );
        byte[] what = toByteArray( obj );
        file.writeInt( what.length );
        file.write( what );
        file.setLength( file.getFilePointer() );
        return result;
    }

    public static Object readObject( RandomAccessFile file, long position ) 
            throws IOException, ClassNotFoundException {
        file.seek( position );
        int length = file.readInt();
        byte[] what = new byte[length];
        file.read( what );
        return fromByteArray( what );
    }
}
