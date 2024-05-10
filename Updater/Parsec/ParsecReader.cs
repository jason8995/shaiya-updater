using System.Text;
using Parsec.Common;
using Parsec.Serialization;
using Parsec.Shaiya.Core;
using Parsec.Shaiya.Data;

namespace Parsec;

public static class ParsecReader
{
    /// <summary>
    /// Reads a shaiya file format from a file
    /// </summary>
    /// <param name="path">File path</param>
    /// <param name="episode">File episode</param>
    /// <param name="encoding">File encoding</param>
    /// <typeparam name="T">Shaiya File Format Type</typeparam>
    /// <returns>T instance</returns>
    public static T FromFile<T>(string path, Episode episode = Episode.EP5, Encoding? encoding = null) where T : FileBase, new()
    {
        var serializationOptions = new BinarySerializationOptions(episode, encoding);
        return FileBase.ReadFromFile<T>(path, serializationOptions);
    }

    /// <summary>
    /// Reads a shaiya file format from a file
    /// </summary>
    /// <param name="path">File path</param>
    /// <param name="episode">File episode</param>
    /// <param name="encoding">File encoding</param>
    /// <typeparam name="T">Shaiya File Format Type</typeparam>
    public static Task<T> FromFileAsync<T>(string path, Episode episode = Episode.EP5, Encoding? encoding = null) where T : FileBase, new()
    {
        return Task.FromResult(FromFile<T>(path, episode, encoding));
    }

    /// <summary>
    /// Reads the shaiya file format from a file
    /// </summary>
    /// <param name="path">File path</param>
    /// <param name="type">FileBase child type to be read</param>
    /// <param name="episode">File episode</param>
    /// <param name="encoding">File encoding</param>
    /// <returns>FileBase instance</returns>
    public static FileBase FromFile(string path, Type type, Episode episode = Episode.EP5, Encoding? encoding = null)
    {
        var serializationOptions = new BinarySerializationOptions(episode, encoding);
        return FileBase.ReadFromFile(path, type, serializationOptions);
    }

    /// <summary>
    /// Reads the shaiya file format from a file
    /// </summary>
    /// <param name="path">File path</param>
    /// <param name="type">FileBase child type to be read</param>
    /// <param name="episode">File episode</param>
    /// <param name="encoding">File encoding</param>
    public static Task<FileBase> FromFileAsync(string path, Type type, Episode episode = Episode.EP5, Encoding? encoding = null)
    {
        return Task.FromResult(FromFile(path, type, episode, encoding));
    }

    /// <summary>
    /// Reads a shaiya file format from a buffer (byte array)
    /// </summary>
    /// <param name="name">File name</param>
    /// <param name="buffer">File buffer</param>
    /// <param name="episode">File episode</param>
    /// <param name="encoding">File encoding</param>
    /// <typeparam name="T">Shaiya File Format Type</typeparam>
    /// <returns>T instance</returns>
    public static T FromBuffer<T>(string name, byte[] buffer, Episode episode = Episode.EP5, Encoding? encoding = null) where T : FileBase, new()
    {
        var serializationOptions = new BinarySerializationOptions(episode, encoding);
        return FileBase.ReadFromBuffer<T>(name, buffer, serializationOptions);
    }

    /// <summary>
    /// Reads a shaiya file format from a buffer (byte array)
    /// </summary>
    /// <param name="name">File name</param>
    /// <param name="buffer">File buffer</param>
    /// <param name="episode">File episode</param>
    /// <param name="encoding">File encoding</param>
    /// <typeparam name="T">Shaiya File Format Type</typeparam>
    public static Task<T> FromBufferAsync<T>(string name, byte[] buffer, Episode episode = Episode.EP5, Encoding? encoding = null) where T : FileBase, new()
    {
        return Task.FromResult(FromBuffer<T>(name, buffer, episode));
    }

    /// <summary>
    /// Reads the shaiya file format from a buffer (byte array)
    /// </summary>
    /// <param name="name">File name</param>
    /// <param name="buffer">File buffer</param>
    /// <param name="type">FileBase child type to be read</param>
    /// <param name="episode">File episode</param>
    /// <param name="encoding">File encoding</param>
    /// <returns>FileBase instance</returns>
    public static FileBase FromBuffer(string name, byte[] buffer, Type type, Episode episode = Episode.EP5, Encoding? encoding = null)
    {
        var serializationOptions = new BinarySerializationOptions(episode, encoding);
        return FileBase.ReadFromBuffer(name, buffer, type, serializationOptions);
    }

    /// <summary>
    /// Reads the shaiya file format from a buffer (byte array)
    /// </summary>
    /// <param name="name">File name</param>
    /// <param name="buffer">File buffer</param>
    /// <param name="type">FileBase child type to be read</param>
    /// <param name="episode">File episode</param>
    /// <param name="encoding">File encoding</param>
    public static Task<FileBase> FromBufferAsync(string name, byte[] buffer, Type type, Episode episode = Episode.EP5, Encoding? encoding = null)
    {
        return Task.FromResult(FromBuffer(name, buffer, type, episode, encoding));
    }

    /// <summary>
    /// Reads the shaiya file format from a buffer (byte array) within a <see cref="Data"/> instance
    /// </summary>
    /// <param name="data"><see cref="Data"/> instance</param>
    /// <param name="file"><see cref="SFile"/> instance</param>
    /// <param name="episode">File episode</param>
    /// <param name="encoding">File encoding</param>
    /// <returns>FileBase instance</returns>
    public static T FromData<T>(Data data, SFile file, Episode episode = Episode.EP5, Encoding? encoding = null) where T : FileBase, new()
    {
        var serializationOptions = new BinarySerializationOptions(episode, encoding);
        return FileBase.ReadFromData<T>(data, file, serializationOptions);
    }

    /// <summary>
    /// Reads the shaiya file format from a buffer (byte array) within a <see cref="Data"/> instance
    /// </summary>
    /// <param name="data"><see cref="Data"/> instance</param>
    /// <param name="file"><see cref="SFile"/> instance</param>
    /// <param name="episode">File episode</param>
    /// <param name="encoding">File encoding</param>
    public static Task<T> FromDataAsync<T>(Data data, SFile file, Episode episode = Episode.EP5, Encoding? encoding = null) where T : FileBase, new()
    {
        return Task.FromResult(FromData<T>(data, file, episode, encoding));
    }

    /// <summary>
    /// Reads the shaiya file format from a buffer (byte array) within a <see cref="Data"/> instance
    /// </summary>
    /// <param name="data"><see cref="Data"/> instance</param>
    /// <param name="file"><see cref="SFile"/> instance</param>
    /// <param name="type">FileBase child type to be read</param>
    /// <param name="episode">File episode</param>
    /// <param name="encoding">File encoding</param>
    /// <returns>FileBase instance</returns>
    public static FileBase FromData(Data data, SFile file, Type type, Episode episode = Episode.EP5, Encoding? encoding = null)
    {
        var serializationOptions = new BinarySerializationOptions(episode, encoding);
        return FileBase.ReadFromData(data, file, type, serializationOptions);
    }

    /// <summary>
    /// Reads the shaiya file format from a buffer (byte array) within a <see cref="Data"/> instance
    /// </summary>
    /// <param name="data"><see cref="Data"/> instance</param>
    /// <param name="file"><see cref="SFile"/> instance</param>
    /// <param name="type">FileBase child type to be read</param>
    /// <param name="episode">File episode</param>
    /// <param name="encoding">File encoding</param>
    public static Task<FileBase> FromDataAsync(Data data, SFile file, Type type, Episode episode = Episode.EP5, Encoding? encoding = null)
    {
        return Task.FromResult(FromData(data, file, type, episode, encoding));
    }
}
