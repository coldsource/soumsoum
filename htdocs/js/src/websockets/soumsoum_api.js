 /*
  * This file is part of evQueue
  *
  * evQueue is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * evQueue is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with evQueue. If not, see <http://www.gnu.org/licenses/>.
  *
  * Author: Thibault Kummer
  */

export class SoumsoumAPI
{
	constructor(parameters)
	{
	}
	
	connect(app)
	{
		var self = this;
		
		self.ws = new WebSocket("ws://localhost:7000", "api");
		
		// Event on connection
		self.ws.onopen = function (event) {
			console.log("Connected");
		};
			
		// Event on disconnection
		self.ws.onclose = function(event) {
			console.log("Disconnected");
		}
			
		self.ws.onmessage = function (event) {
			app.setState({data: JSON.parse(event.data)});
		}
	}
	
	command(data) {
		this.ws.send(JSON.stringify(data));
	}
}
