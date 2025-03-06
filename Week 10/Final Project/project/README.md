# MYRECIPES WEB APPLICATION
#### Video Demo: https://youtu.be/c2erWba9aRU
#### Description:
First and foremost, it's essential to acknowledge that this project is the result of a collaboration between two passionate individuals: myself, Diego Agudelo, and Ralph Balazs, a former student of the CS50 course. Both students at the 42 school in Paris, we are proud and excited to have contributed to this innovative project.

Our application is designed to allow everyone to add and share their own culinary recipes. It offers an accessible and user-friendly platform where users can discover the culinary creations of others, even without prior registration.

A key aspect of the application is its intuitive recipe management. Users can easily modify their recipes while retaining the original information. Additionally, to facilitate navigation, the site is organized into three main categories: 'Culinary Arts' for main dishes and starters, 'Bakery' for bakery recipes, and 'Pastry' for desserts and sweet food preparations.

We have also integrated several tools to optimize site management and ensure user security:

An administrator page for managing user accounts. Admin username: admin, password: 12345
Password encryption to strengthen the security of personal data.
A password recovery system based on the user's first and last name.
The ability to modify one's user profile at any time.

To visualize the functioning of the application, we invite you to use:
- Username: Maite
- Password: 12.

In order to facilitate testing of the site, we suggest using the following credentials:
- Username: test
- Password: 123

Furthermore, we have also installed the following Python extensions to assist us in creating the application: # pip install Flask-Mail Flask-Session Werkzeug pip3 install cs50.
This project was conceived with the goal of simplifying the sharing and recording of culinary recipes, thus offering a platform for cooking enthusiasts of all levels to explore, learn, and be inspired.

Additionally, we encountered the following difficulties:

- We were unable to implement the mail sending system as it required synchronizing an online SMTP service, and in most cases, it was a paid service. We tried to use Google's services without any success.
- We faced many challenges with the website design since we used Adobe XD, but we could only export in .svg format. Converting it to HTML was not straightforward; it required using Figma and manually correcting. Subsequently, we had issues with scaling each text and button, which we resolved by replacing pixels with percentages and viewport widths (vw) to allow automatic scaling on smaller screens like mobile phones.
- We also encountered problems with the "GET" and "POST" system in Flask, as it was essential to understand the complexity of the system when receiving and modifying data.

Improvement areas we wanted to add:

- Implement a password recovery system via email.
- Allow users to comment on and rate other people's recipes.
- Enforce password security rules (use of special characters, integers, and a minimum character count).
- Limit the number of characters in text fields to avoid database issues and improve server efficiency.
- Improve the recipe display design for a more ergonomic experience (such as an icon display like on a smartphone, adding subcategories, etc.).
- Enhance the website's SEO (target specific keywords, for instance).
