import java.io.*;
import java.util.zip.*;

public class Buffer {
    static final String zipEntryName = "z";
	
    static byte[] toByteArray( Serializable obj ) throws IOException {
        ByteArrayOutputStream bufOut = new ByteArrayOutputStream();
        try ( ObjectOutputStream oos = new ObjectOutputStream( bufOut )) {
            oos.writeObject( obj );
            oos.flush();
            return bufOut.toByteArray();
        }
    }
		
    static byte[] toZipByteArray( Serializable obj ) throws IOException {
        ByteArrayOutputStream bufOut = new ByteArrayOutputStream();
        try ( ZipOutputStream zos = new ZipOutputStream( bufOut )) {
            zos.putNextEntry( new ZipEntry( zipEntryName ));
            zos.setLevel( ZipOutputStream.DEFLATED );
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
        try ( ObjectInputStream ois = new ObjectInputStream( bufIn )) {
            return ois.readObject();
        }
    }
	
    static Object fromZipByteArray( byte[] arr ) 
            throws IOException, ClassNotFoundException {
        ByteArrayInputStream  bufIn = new ByteArrayInputStream( arr );
        try( ZipInputStream zis = new ZipInputStream( bufIn )) {
            ZipEntry zen = zis.getNextEntry();
            if ( zen.getName().equals(zipEntryName)== false ) {
                throw new IOException("Invalid block format");
            }
            try ( ObjectInputStream ois = new ObjectInputStream( zis )) {
                return ois.readObject();
            }
        }
    }
	
    public static long writeObject( RandomAccessFile file, Serializable obj, 
            Boolean zipped ) throws IOException {
        long result = file.length();
        file.seek( result );
        byte[] what;
        if ( zipped ) {
            what = toZipByteArray( obj );
            file.writeByte(1);
	} 
        else {
            what = toByteArray( obj );
            file.writeByte(0);
        }
        file.writeInt( what.length );
        file.write( what );
        file.setLength( file.getFilePointer() );
        return result;
    }

    public static Object readObject( RandomAccessFile file, long position, 
            boolean[] wasZipped ) throws IOException, ClassNotFoundException {
        file.seek( position );
        byte zipped = file.readByte();
        int length = file.readInt();
        byte[] what = new byte[length];
        file.read( what );
        if ( wasZipped != null ) {
            wasZipped[0] = ( zipped != 0 ); 
        }    
        if ( zipped == 0 ) {
            return fromByteArray( what );		
        } 
        else if ( zipped == 1 ){
            return fromZipByteArray( what );					
        }
        else {
            throw new IOException("Invalid block format");
        }
    }
}
