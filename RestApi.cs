using System;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Threading.Tasks;
using System.Collections.Generic;
using System.Text.Json; // For .NET Core 3.1+ or System.Text.Json NuGet package
// using Newtonsoft.Json; // Alternative for older .NET versions or if preferred

public class Post
{
    public int UserId { get; set; }
    public int Id { get; set; }
    public string Title { get; set; }
    public string Body { get; set; }
}

public class RestApiClient
{
    private static readonly HttpClient client = new HttpClient();

    public static async Task Main(string[] args)
    {
        // Configure HttpClient
        client.BaseAddress = new Uri("https://jsonplaceholder.typicode.com/");
        client.DefaultRequestHeaders.Accept.Clear();
        client.DefaultRequestHeaders.Accept.Add(new MediaTypeWithQualityHeaderValue("application/json"));

        try
        {
            // Make a GET request to the /posts endpoint
            HttpResponseMessage response = await client.GetAsync("posts");

            // Ensure the request was successful
            if (response.IsSuccessStatusCode)
            {
                // Read the response content as a string
                string responseBody = await response.Content.ReadAsStringAsync();

                // Deserialize the JSON response into a list of Post objects
                List<Post> posts = JsonSerializer.Deserialize<List<Post>>(responseBody); 
                // Alternatively with Newtonsoft.Json: List<Post> posts = JsonConvert.DeserializeObject<List<Post>>(responseBody);

                // Process the retrieved data
                foreach (var post in posts)
                {
                    Console.WriteLine($"ID: {post.Id}, Title: {post.Title}");
                }
            }
            else
            {
                Console.WriteLine($"Error: {response.StatusCode} - {response.ReasonPhrase}");
            }
        }
        catch (HttpRequestException e)
        {
            Console.WriteLine($"Request Exception: {e.Message}");
        }
        catch (JsonException e)
        {
            Console.WriteLine($"JSON Deserialization Error: {e.Message}");
        }
        catch (Exception e)
        {
            Console.WriteLine($"An unexpected error occurred: {e.Message}");
        }
    }
}
